`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/10/08 14:29:07
// Design Name: 
// Module Name: week5_20191578_1_bit_tb
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


module week5_20191578_1_bit_tb;
reg a, b;
wire c, d, e, f;

week5_20191578_1_bit u1(
    .A(a), .B(b), .C(c), .D(d), .E(e), .F(f)
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
