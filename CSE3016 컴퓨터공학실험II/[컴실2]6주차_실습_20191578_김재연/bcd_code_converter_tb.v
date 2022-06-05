`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/10/12 02:32:27
// Design Name: 
// Module Name: bcd_code_converter_tb
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


module bcd_code_converter_tb;
reg a, b, c, d;
wire f0, f1, f2, f3;

bcd_code_converter u1(
    .A(a), .B(b), .C(c), .D(d), .F0(f0), .F1(f1), .F2(f2), .F3(f3)
);

initial begin
    a=1'b0;
    b=1'b0;
    c=1'b0;
    d=1'b0;
end

always a = #400 ~a;
always b = #200 ~b;
always c = #100 ~c;
always d = #50 ~d;

initial begin
    #500
    $finish;
end



endmodule
