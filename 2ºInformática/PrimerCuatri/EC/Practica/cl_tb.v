`timescale 1 ns / 10 ps

module c1_tb;
    reg a, b, c, d;
    reg [1:0] S;
    wire out;

    cl uut (
        .out(out),
        .a(a),
        .b(b),
        .S(S)
    );

    initial begin

        $dumpfile("cl_tb.vcd");
        $dumpvars;

        $monitor("Time=%0t | S=%b | a=%b | b=%b | c=%b | d=%b | out=%b", $time, S, a, b, out);

        a = 1'b0; b = 1'b0; S = 2'b00; #10;
        a = 1'b0; b = 1'b1; S = 2'b01; #10;
        a = 1'b0; b = 1'b0; S = 2'b10; #10;
        a = 1'b0; b = 1'b0; S = 2'b11; #10;

        a = 1'b1; b = 1'b0; S = 2'b00; #10;
        a = 1'b1; b = 1'b1; S = 2'b01; #10;
        a = 1'b1; b = 1'b0; S = 2'b10; #10;
        a = 1'b0; b = 1'b1; S = 2'b11; #10;

        $finish;
    end
endmodule