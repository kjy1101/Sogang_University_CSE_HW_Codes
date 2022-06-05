`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/11/23 01:36:53
// Design Name: 
// Module Name: decade_counter_tb
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////
module decade_counter_tb();
reg clk, x;
wire a, b, c, d, z;
decade_counter connect(clk, a, b, c, d, x, z);
initial begin
    clk=0; x=0;
end
always clk = #5 ~clk;
always x = #10 ~x;
initial begin
    #1000
    $finish;
end
endmodule
