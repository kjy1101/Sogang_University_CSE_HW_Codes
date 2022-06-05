`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/10/08 00:09:35
// Design Name: 
// Module Name: week5_20191578_de_morgan_1_a_tb
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


module week5_20191578_de_morgan_1_a_tb;
reg a, b;
wire c;

week5_20191578_de_morgan_1_a u1(
    .A(a), .B(b), .C(c)
);

initial begin
    a = 1'b0;
    b = 1'b0;
end

always a = #100 ~a;
always b = #50 ~b;

initial begin
    #200
    $finish;
end

endmodule
