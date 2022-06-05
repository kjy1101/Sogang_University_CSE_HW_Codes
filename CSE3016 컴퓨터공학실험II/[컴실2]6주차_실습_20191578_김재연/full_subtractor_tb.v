`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/10/11 23:42:31
// Design Name: 
// Module Name: full_subtractor_tb
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


module full_subtractor_tb;
reg a, b, brin;
wire d, brout;

full_subtractor u1(
    .A(a), .B(b), .Brin(brin), .D(d), .Brout(brout)
);

initial begin
    a=1'b0;
    b=1'b0;
    brin=1'b0;
end

always a = #200 ~a;
always b = #100 ~b;
always brin = #50 ~brin;

initial begin
    #400
    $finish;
end
endmodule
