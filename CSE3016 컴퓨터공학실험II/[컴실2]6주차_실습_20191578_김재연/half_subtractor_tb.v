`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/10/11 23:28:55
// Design Name: 
// Module Name: half_subtractor_tb
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


module half_subtractor_tb;
reg a, b;
wire d, br;

half_subtractor u1(
    .A(a), .B(b), .D(d), .Br(br)
);

initial begin
    a=1'b0;
    b=1'b0;
end

always a = #100 ~a;
always b = #50 ~b;

initial begin
    #200
    $finish;
end

endmodule
