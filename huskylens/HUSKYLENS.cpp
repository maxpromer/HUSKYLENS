#include <stdio.h>
#include <string.h>
#include "esp_system.h"
#include "kidbright32.h"
#include "HUSKYLENS.h"
#include "esp_log.h"

#define TAG "HUSKYLENS"

HUSKYLENS::HUSKYLENS(int bus_ch, int dev_addr) {
	channel = bus_ch;
	address = dev_addr;
	polling_ms = HUSKYLENS_POLLING_MS;
}

void HUSKYLENS::init(void) {
	esp_log_level_set("*", ESP_LOG_VERBOSE);

	state = s_detect;
}

int HUSKYLENS::prop_count(void) {
	return 0;
}

bool HUSKYLENS::prop_name(int index, char *name) {
	// not supported
	return false;
}

bool HUSKYLENS::prop_unit(int index, char *unit) {
	// not supported
	return false;
}

bool HUSKYLENS::prop_attr(int index, char *attr) {
	// not supported
	return false;
}

bool HUSKYLENS::prop_read(int index, char *value) {
	// not supported
	return false;
}

bool HUSKYLENS::prop_write(int index, char *value) {
	// not supported
	return false;
}

void HUSKYLENS::process(Driver *drv) {
	i2c = (I2CDev *)drv;
	
	switch (state) {
		case s_detect:
			// detect i2c device
			if (i2c->detect(channel, address) == ESP_OK) {	
				if (i2c->write(channel, address, cmd_req_knock, cmd_req_knock_size) == ESP_OK) {
					uint8_t buffer[cmd_return_ok_size];
					if (i2c->read(channel, address, NULL, 0, buffer, cmd_return_ok_size) == ESP_OK) {
						if (memcmp(buffer, cmd_return_ok, cmd_return_ok_size) == 0) {
							// set initialized flag
							initialized = true;
								
							// clear error flag
							error = false;

							state = s_read;
						} else {
							state = s_error;
						}
					} else {
						state = s_error;
					}
				} else {
					state = s_error;
				}
			} else {
				state = s_error;
			}
			break;

		case s_read: {
			if (!is_tickcnt_elapsed(tickcnt, polling_ms)) {
				break;
			}
			tickcnt = get_tickcnt();

			
			if (i2c->write(channel, address, cmd_req, cmd_req_size) != ESP_OK) {
				state = s_error;
				ESP_LOGE(TAG, "send COMMAND_REQUEST fail");
				break;
			}

			uint8_t buffer[16];
			if (i2c->read(channel, address, NULL, 0, buffer, 16) != ESP_OK) {
				state = s_error;
				ESP_LOGE(TAG, "read COMMAND_RETURN_INFO fail");
				break;
			}

			if (memcmp(buffer, cmd_return_info, 5) != 0) { // invalid header
				state = s_error;
				ESP_LOGE(TAG, "COMMAND_RETURN_INFO invalid header");
				break;
			}

			blocksLen = (buffer[6] << 8) | buffer[5];
			learnedLen = (buffer[8] << 8) | buffer[7];

			if (blocksLen > HUSKYLENS_MAX_BLOCK_SIZE) {
				blocksLen = HUSKYLENS_MAX_BLOCK_SIZE;
			}

			for (int inx=0;inx<blocksLen;inx++) {
				if (i2c->read(channel, address, NULL, 0, buffer, 16) != ESP_OK) {
					state = s_error;
					ESP_LOGE(TAG, "read COMMAND_RETURN_xxx fail");
					break;
				}

				if (memcmp(buffer, cmd_return_block, 5) == 0) { // is COMMAND_RETURN_BLOCK header ?
					blocks[inx].type = IS_BLOCK;
					blocks[inx].x = (buffer[6] << 8) | buffer[5];
					blocks[inx].y = (buffer[8] << 8) | buffer[7];
					blocks[inx].w = (buffer[10] << 8) | buffer[9];
					blocks[inx].h = (buffer[12] << 8) | buffer[11];
					blocks[inx].id = (buffer[14] << 8) | buffer[13];
				} else if (memcmp(buffer, cmd_return_arrow, 5) == 0) { // is COMMAND_RETURN_ARROW header ?
					blocks[inx].type = IS_ARROW;
					blocks[inx].xs = (buffer[6] << 8) | buffer[5];
					blocks[inx].ys = (buffer[8] << 8) | buffer[7];
					blocks[inx].xe = (buffer[10] << 8) | buffer[9];
					blocks[inx].ye = (buffer[12] << 8) | buffer[11];
					blocks[inx].id = (buffer[14] << 8) | buffer[13];
				} else {
					state = s_error;
					ESP_LOGE(TAG, "COMMAND_RETURN_xxx invalid header");
					break;
				}
			}

			break;
		}

		case s_error:
			// set error flag
			error = true;
			// clear initialized flag
			initialized = false;
			// get current tickcnt
			tickcnt = get_tickcnt();
			// goto wait and retry with detect state
			state = s_wait;
			break;

		case s_wait:
			// wait polling_ms timeout
			if (is_tickcnt_elapsed(tickcnt, polling_ms)) {
				state = s_detect;
			}
			break;
	}
}

bool HUSKYLENS::isReady() {
	return !error;
}

void HUSKYLENS::setAlgorithm(int mode) {
	uint8_t buff[cmd_req_alg_size];
	memcpy(buff, cmd_req_alg, cmd_req_alg_size);
	buff[5] = mode;
	buff[7] = 0x3F + mode;
	if (i2c->write(channel, address, buff, cmd_req_alg_size) == ESP_OK) {
		uint8_t buffer[cmd_return_ok_size];
		if (i2c->read(channel, address, NULL, 0, buffer, cmd_return_ok_size) != ESP_OK) {
			if (memcmp(buffer, cmd_return_ok, cmd_return_ok_size) != 0) {
				state = s_error;
			}
		} else {
			state = s_error;
		}
	} else {
		state = s_error;
	}
}

int HUSKYLENS::getIdIndex(int index, BlockType type) {
	int blockIndex = -1;
	for (int inx=0;inx<blocksLen;inx++) {
		if (blocks[inx].id == index && blocks[inx].type == type) {
			blockIndex = inx;
			break;
		}
	}

	return blockIndex;
}

bool HUSKYLENS::blockIsReady(int index) {
	return getIdIndex(index, IS_BLOCK) >= 0;
}

int HUSKYLENS::blockGetPos(int index, int axis) {
	int blockIndex = getIdIndex(index, IS_BLOCK);
	if (blockIndex < 0) {
		return -1;
	}

	if (axis == 0) {
		return blocks[blockIndex].x;
	} else if (axis == 1) {
		return blocks[blockIndex].y;
	}

	return -1;
}

int HUSKYLENS::blockGetSize(int index, int axis) {
	int blockIndex = getIdIndex(index, IS_BLOCK);
	if (blockIndex < 0) {
		return -1;
	}

	if (axis == 0) {
		return blocks[blockIndex].w;
	} else if (axis == 1) {
		return blocks[blockIndex].h;
	}

	return -1;
}

bool HUSKYLENS::arrowIsReady() {
	int arrowIndex;

	arrowIndex = getIdIndex(0, IS_ARROW);
	if (arrowIndex >= 0) {
		return true;
	}

	arrowIndex = getIdIndex(1, IS_ARROW);
	if (arrowIndex >= 0) {
		return true;
	}
	return false;
}

int HUSKYLENS::arrowGetPos(int axis) {
	int arrowIndex;
	arrowIndex = getIdIndex(0, IS_ARROW);
	if (arrowIndex < 0) {
		arrowIndex = getIdIndex(1, IS_ARROW);
		if (arrowIndex < 0) {
			return -1;
		}
	}

	if (axis == 0) {
		return blocks[arrowIndex].xs;
	} else if (axis == 1) {
		return blocks[arrowIndex].ys;
	} else if (axis == 2) {
		return blocks[arrowIndex].xe;
	} else if (axis == 3) {
		return blocks[arrowIndex].ye;
	}

	return -1;
}
