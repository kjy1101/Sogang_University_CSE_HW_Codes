`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/11/23 23:22:09
// Design Name: 
// Module Name: two_four_counter_tb
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


module two_four_counter_tb();
reg clk, x;
wire a,b,c,d,z;
two_four_counter connect(clk, a,b,c,d,x,z);
initial begin
    clk=0; x=0;
end
always clk = #5 ~clk;
always x = #10 ~x;
endmodule
