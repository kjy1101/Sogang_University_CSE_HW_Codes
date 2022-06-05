`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/10/11 23:10:18
// Design Name: 
// Module Name: full_adder_tb
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


module full_adder_tb;
reg a, b, cin;
wire s, cout;

full_adder u1(
    .A(a), .B(b), .Cin(cin), .S(s), .Cout(cout)
);

initial begin
    a=1'b0;
    b=1'b0;
    cin=1'b0;
end

always a = #200 ~a;
always b = #100 ~b;
always cin = #50 ~cin;

initial begin
    #400
    $finish;
end

endmodule
