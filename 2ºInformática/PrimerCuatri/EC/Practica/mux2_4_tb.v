`timescale 1ns / 10ps

module tb_mux2_4;


reg [3:0] A;
reg [3:0] B;
reg s;
wire [3:0] Out;


mux2_4 uut (
    .Out(Out),
    .A(A),
    .B(B),
    .s(s)
);

initial begin
    $monitor("Time=%0t | S=%b | a=%b | b=%b | c=%b | d=%b | out=%b", $time, s, A, B, Out);
    $dumpfile("mux2_4_tb.vcd");
    $dumpvars;

    A = 4'b0000; 
    B = 4'b1111; 
    s = 0;

    #10;

    s = 1;
    #10;

    A = 4'b1010; 
    B = 4'b0101; 
    s = 0;
    #10;

    s = 1;
    #10;

    A = 4'b1110; 
    B = 4'b0001; 
    s = 0;
    #10;

    s = 1;
    #10;
    
    $finish;
end

endmodule