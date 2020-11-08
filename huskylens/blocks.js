Blockly.Blocks['huskylens_is_ready'] = {
    init: function () {
        this.jsonInit({
            "type": "huskylens_is_ready",
            "message0": Blockly.Msg.HUSKYLENS_IS_READY_MESSAGE,
            "output": [
                "Boolean",
                "Number"
            ],
            "colour": 15,
            "tooltip": Blockly.Msg.HUSKYLENS_IS_READY_TOOLTIP,
            "helpUrl": ""
          });
    }
};


Blockly.Blocks['huskylens_mode'] = {
    init: function () {
        this.jsonInit({
            "type": "huskylens_mode",
            "message0": Blockly.Msg.HUSKYLENS_MODE_MESSAGE,
            "args0": [
              {
                "type": "field_dropdown",
                "name": "algorithm",
                "options": [
                  [
                    "Face Recognition",
                    "FACE_RECOGNITION"
                  ],
                  [
                    "Object Tracking",
                    "OBJECT_TRACKING"
                  ],
                  [
                    "Obejct Recognition",
                    "OBJECT_RECOGNITION"
                  ],
                  [
                    "Line Tracking",
                    "LINE_TRACKING"
                  ],
                  [
                    "Color Recognition",
                    "COLOR_RECOGNITION"
                  ],
                  [
                    "Tag Recognition",
                    "TAG_RECOGNITION"
                  ],
                  [
                    "Object Classification",
                    "CLASSIFICATION"
                  ]
                ]
              }
            ],
            "previousStatement": null,
            "nextStatement": null,
            "colour": 15,
            "tooltip": Blockly.Msg.HUSKYLENS_MODE_TOOLTIP,
            "helpUrl": ""
        });
    }
};


Blockly.Blocks['huskylens_block_is_ready'] = {
    init: function () {
        this.jsonInit({
            "type": "huskylens_block_is_ready",
            "message0": Blockly.Msg.HUSKYLENS_BLOCK_IS_READY_MESSAGE,
            "args0": [
              {
                "type": "input_value",
                "name": "id",
                "check": "Number"
              }
            ],
            "output": [
                "Boolean",
                "Number"
            ],
            "colour": 15,
            "tooltip": Blockly.Msg.HUSKYLENS_BLOCK_IS_READY_TOOLTIP,
            "helpUrl": ""
        });
    },
	xmlToolbox: function() {
		return `
		<block type="huskylens_block_is_ready">
			<value name="id">
				<shadow type="math_number">
					<field name="VALUE">0</field>
				</shadow>
			</value>
		</block>
		`;
	}
};

Blockly.Blocks['huskylens_block_get_pos'] = {
    init: function () {
        this.jsonInit({
            "type": "huskylens_block_get_pos",
            "message0": Blockly.Msg.HUSKYLENS_BLOCK_GET_POS_MESSAGE,
            "args0": [
              {
                "type": "input_value",
                "name": "id",
                "check": "Number"
              },
              {
                "type": "field_dropdown",
                "name": "axis",
                "options": [
                  [
                    "x",
                    "0"
                  ],
                  [
                    "y",
                    "1"
                  ]
                ]
              }
            ],
            "output": "Number",
            "colour": 15,
            "tooltip": Blockly.Msg.HUSKYLENS_BLOCK_GET_POS_TOOLTIP,
            "helpUrl": ""
        });
    },
	xmlToolbox: function() {
		return `
		<block type="huskylens_block_get_pos">
			<value name="id">
				<shadow type="math_number">
					<field name="VALUE">0</field>
				</shadow>
			</value>
		</block>
		`;
	}
};

Blockly.Blocks['huskylens_block_get_size'] = {
    init: function () {
        this.jsonInit({
            "type": "huskylens_block_get_size",
            "message0": Blockly.Msg.HUSKYLENS_BLOCK_GET_SIZE_MESSAGE,
            "args0": [
              {
                "type": "input_value",
                "name": "id",
                "check": "Number"
              },
              {
                "type": "field_dropdown",
                "name": "val",
                "options": [
                  [
                    "width",
                    "0"
                  ],
                  [
                    "height",
                    "1"
                  ]
                ]
              }
            ],
            "output": "Number",
            "colour": 15,
            "tooltip": Blockly.Msg.HUSKYLENS_BLOCK_GET_SIZE_TOOLTIP,
            "helpUrl": ""
        });
    },
	xmlToolbox: function() {
		return `
		<block type="huskylens_block_get_size">
			<value name="id">
				<shadow type="math_number">
					<field name="VALUE">0</field>
				</shadow>
			</value>
		</block>
		`;
	}
};

Blockly.Blocks['huskylens_arrow_is_ready'] = {
    init: function () {
        this.jsonInit({
            "type": "huskylens_arrow_is_ready",
            "message0": Blockly.Msg.HUSKYLENS_ARROW_IS_READY_MESSAGE,
            "output": [
                "Boolean",
                "Number"
            ],
            "colour": 15,
            "tooltip": Blockly.Msg.HUSKYLENS_ARROW_IS_READY_TOOLTIP,
            "helpUrl": ""
        });
    }
};

Blockly.Blocks['huskylens_arrow_get_pos'] = {
    init: function () {
        this.jsonInit({
            "type": "huskylens_arrow_get_pos",
            "message0": Blockly.Msg.HUSKYLENS_ARROW_GET_POS_MESSAGE,
            "args0": [
              {
                "type": "field_dropdown",
                "name": "axis",
                "options": [
                  [
                    "x arrowhead",
                    "2"
                  ],
                  [
                    "y arrowhead",
                    "3"
                  ],
                  [
                    "x origin",
                    "0"
                  ],
                  [
                    "y origin",
                    "1"
                  ]
                ]
              }
            ],
            "output": "Number",
            "colour": 15,
            "tooltip": Blockly.Msg.HUSKYLENS_ARROW_GET_POS_TOOLTIP,
            "helpUrl": ""
        });
    }
};
