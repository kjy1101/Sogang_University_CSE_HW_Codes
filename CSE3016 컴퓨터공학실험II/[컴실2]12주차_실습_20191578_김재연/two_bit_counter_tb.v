`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/11/19 22:37:56
// Design Name: 
// Module Name: two_bit_counter_tb
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
module two_bit_counter_tb();
reg clk, x;
wire a, b, z;
two_bit_counter connect(clk, a, b, x, z);
initial begin
clk=0; x=0;
x <= #10 1;
x <= #30 0;
x <= #60 1;
x <= #100 0;
x <= #120 1;
x <= #130 0;
x <= #150 1;
x <= #180 0;
end
always clk = #5 ~clk;
initial begin
    #200
    $finish;
end
endmodule
