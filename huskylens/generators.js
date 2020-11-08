const HUSKYLENS = 'DEV_I2C1.HUSKYLENS(0, 0x32)';

Blockly.JavaScript['huskylens_is_ready'] = function (block) {
    var code = `${HUSKYLENS}.isReady()`;
    return [code, Blockly.JavaScript.ORDER_NONE];
};

Blockly.JavaScript['huskylens_mode'] = function (block) {
    var dropdown_algorithm = block.getFieldValue('algorithm');

    var code = `${HUSKYLENS}.setAlgorithm(${HUSKYLENS}.${dropdown_algorithm});\n`;
    return code;
};

Blockly.JavaScript['huskylens_block_is_ready'] = function (block) {
    var value_id = Blockly.JavaScript.valueToCode(block, 'id', Blockly.JavaScript.ORDER_ATOMIC);

    var code = `${HUSKYLENS}.blockIsReady(${value_id})`;
    return [code, Blockly.JavaScript.ORDER_NONE];
};

Blockly.JavaScript['huskylens_block_get_pos'] = function (block) {
    var value_id = Blockly.JavaScript.valueToCode(block, 'id', Blockly.JavaScript.ORDER_ATOMIC);
    var dropdown_axis = block.getFieldValue('axis');

    var code = `${HUSKYLENS}.blockGetPos(${value_id}, ${dropdown_axis})`;
    return [code, Blockly.JavaScript.ORDER_NONE];
};

Blockly.JavaScript['huskylens_block_get_size'] = function (block) {
    var value_id = Blockly.JavaScript.valueToCode(block, 'id', Blockly.JavaScript.ORDER_ATOMIC);
    var dropdown_val = block.getFieldValue('val');

    var code = `${HUSKYLENS}.blockGetSize(${value_id}, ${dropdown_val})`;
    return [code, Blockly.JavaScript.ORDER_NONE];
};

Blockly.JavaScript['huskylens_arrow_is_ready'] = function (block) {
    var code = `${HUSKYLENS}.arrowIsReady()`;
    return [code, Blockly.JavaScript.ORDER_NONE];
};

Blockly.JavaScript['huskylens_arrow_get_pos'] = function (block) {
    var dropdown_axis = block.getFieldValue('axis');

    var code = `${HUSKYLENS}.arrowGetPos(${dropdown_axis})`;
    return [code, Blockly.JavaScript.ORDER_NONE];
};
