`timescale 1ns/10ps

module tb_fa;
  reg a, b, c_in;
  wire c_out, sum;


  fa uut (
    .c_out(c_out),
    .sum(sum),
    .a(a),
    .b(b),
    .c_in(c_in)
  );

  initial begin

    $dumpfile("fa_test.vcd");
    $dumpvars(0, tb_fa);

    $monitor("Time = %0t | a = %b | b = %b | c_in = %b | sum = %b | c_out = %b", 
              $time, a, b, c_in, sum, c_out);

    a = 0; b = 0; c_in = 0; #10;
    a = 0; b = 0; c_in = 1; #10;
    a = 0; b = 1; c_in = 0; #10;
    a = 0; b = 1; c_in = 1; #10;
    a = 1; b = 0; c_in = 0; #10;
    a = 1; b = 0; c_in = 1; #10;
    a = 1; b = 1; c_in = 0; #10;
    a = 1; b = 1; c_in = 1; #10;

    $finish;
  end
endmodule
