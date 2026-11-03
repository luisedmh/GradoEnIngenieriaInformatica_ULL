`timescale 1ns / 10ps

module ul4_tb;

  reg [3:0] A, B;
  reg [1:0] S;
  wire [3:0] Out;

  ul4 dut (
    .Out(Out),
    .A(A),
    .B(B),
    .S(S)
  );

  initial begin
    $dumpfile("ul4_tb.vcd");
    $dumpvars(0, ul4_tb);

    $monitor("Time = %0t | A = %b | B = %b | S = %b | Out = %b", $time, A, B, S, Out);

    A = 4'b0000; B = 4'b0000; S = 2'b00;
    #10;
    A = 4'b1010; B = 4'b0101; S = 2'b01;
    #10;
    A = 4'b1111; B = 4'b0000; S = 2'b10;
    #10;
    A = 4'b1100; B = 4'b0011; S = 2'b11;
    #10;

    $finish;
  end

endmodule
