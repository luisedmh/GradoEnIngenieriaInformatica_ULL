`timescale 1ns / 10ps

module tb_sum4;
  reg [3:0] A, B;   
  reg c_in;         
  wire [3:0] S;     
  wire c_out; 

  sum4 uut (
    .S(S),
    .c_out(c_out),
    .A(A),
    .B(B),
    .c_in(c_in)
  );

  initial begin
    $dumpfile("sum4_test.vcd");
    $dumpvars(0, tb_sum4);

    $monitor("Time = %0t | A = %b | B = %b | c_in = %b | S = %b | c_out = %b", 
              $time, A, B, c_in, S, c_out);

    A = 4'b0000; B = 4'b0000; c_in = 0; #10;  // Suma sin acarreo
    A = 4'b0001; B = 4'b0001; c_in = 0; #10;  // Suma simple
    A = 4'b1010; B = 4'b0101; c_in = 0; #10;  // Caso de prueba medio
    A = 4'b1111; B = 4'b1111; c_in = 0; #10;  // Acarreo de salida esperado
    A = 4'b1111; B = 4'b1111; c_in = 1; #10;  // Suma máxima con c_in = 1
    A = 4'b1101; B = 4'b0110; c_in = 1; #10;  // Otro caso con acarreo de entrada

    $finish;
  end
endmodule
