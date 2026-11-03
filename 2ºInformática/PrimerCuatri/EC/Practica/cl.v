module cl(output wire out, input wire a, b, input wire [1:0] S);

    wire w1, w2, w3, w4;
    
    and and1(w1, a, b);
    or or1(w2, a, b);
    xor xor1(w3, a, b);
    not not1(w4, a);

    mux4_1 mux4_11(out, w1, w2, w3, w4, S);

endmodule
