#ifndef __HUSKYLENS_H__
#define __HUSKYLENS_H__

#include "math.h"
#include "driver.h"
#include "device.h"
#include "i2c-dev.h"

#define HUSKYLENS_POLLING_MS 20
#define HUSKYLENS_MAX_BLOCK_SIZE 20

class HUSKYLENS : public Device {
	private:
		enum {
			s_detect, 
			s_read, 
			s_error, 
			s_wait
		} state;
		TickType_t tickcnt, polling_tickcnt;

		I2CDev *i2c;
		
		uint8_t cmd_req_knock[6] = { 0x55, 0xAA, 0x11, 0x00, 0x2C, 0x3C };
		uint8_t cmd_req_knock_size = 6;

		uint8_t cmd_req[6] = { 0x55, 0xAA, 0x11, 0x00, 0x20, 0x30 };
		uint8_t cmd_req_size = 6;

		uint8_t cmd_req_alg[8] = { 0x55, 0xAA, 0x11, 0x02, 0x2D, 0, 0, 0x3F };
		uint8_t cmd_req_alg_size = 8;

		uint8_t cmd_return_ok[6] = { 0x55, 0xAA, 0x11, 0x00, 0x2E, 0x3E };
		uint8_t cmd_return_ok_size = 6;

		uint8_t cmd_return_info[5] = { 0x55, 0xAA, 0x11, 0x0A, 0x29 };
		uint8_t cmd_return_block[5] = { 0x55, 0xAA, 0x11, 0x0A, 0x2A };
		uint8_t cmd_return_arrow[5] = { 0x55, 0xAA, 0x11, 0x0A, 0x2B };

		uint16_t blocksLen, learnedLen;

		enum BlockType {
			IS_BLOCK,
			IS_ARROW
		};

		struct BlockArrowBufferType {
			BlockType type;
			uint16_t id;
			union {
				struct {
					uint16_t x, y, w, h;
				};
				struct {
					uint16_t xs, ys, xe, ye;
				};
			};
		};
		
		struct BlockArrowBufferType blocks[HUSKYLENS_MAX_BLOCK_SIZE];

		int getIdIndex(int index, BlockType type) ;
		
	public:
		// constructor
		HUSKYLENS(int bus_ch, int dev_addr);
		// override
		void init(void);
		void process(Driver *drv);
		int prop_count(void);
		bool prop_name(int index, char *name);
		bool prop_unit(int index, char *unit);
		bool prop_attr(int index, char *attr);
		bool prop_read(int index, char *value);
		bool prop_write(int index, char *value);
		
		// method
		enum {
			FACE_RECOGNITION = 0,
			OBJECT_TRACKING = 1,
			OBJECT_RECOGNITION = 2,
			LINE_TRACKING = 3,
			COLOR_RECOGNITION = 4,
			TAG_RECOGNITION = 5,
			CLASSIFICATION = 6
		};
		
		bool isReady() ;
		void setAlgorithm(int mode) ;

		bool blockIsReady(int index) ;
		int blockGetPos(int index, int axis) ;
		int blockGetSize(int index, int axis) ;

		bool arrowIsReady() ;
		int arrowGetPos(int axis) ;
		
};

#endif
