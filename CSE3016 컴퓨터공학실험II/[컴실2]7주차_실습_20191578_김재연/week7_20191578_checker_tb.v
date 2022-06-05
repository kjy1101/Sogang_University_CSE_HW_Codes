`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/10/19 00:44:03
// Design Name: 
// Module Name: week7_20191578_checker_tb
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


module week7_20191578_checker_tb;
reg a, b, c, d, p;
wire pec;
week7_20191578_checker u1(
    .A(a), .B(b), .C(c), .D(d), .P(p), .PEC(pec)
);
initial begin
    a=1'b0;
    b=1'b0;
    c=1'b0;
    d=1'b0;
    p=1'b0;
end

always a = #160 ~a;
always b = #80 ~b;
always c = #40 ~c;
always d = #20 ~d;
always p = #10 ~p;

initial begin
    #320
    $finish;
end
endmodule
