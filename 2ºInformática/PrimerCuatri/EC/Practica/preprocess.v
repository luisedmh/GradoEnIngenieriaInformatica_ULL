module preprocess(output wire [3:0] AMod, output wire [3:0] BMod, input wire [3:0] A, input wire [3:0] B, input wire [2:0] Op);

    wire add1, op1_A, op2_B, cpl;
    assign add1 = Op[0];
    assign op1_A = Op[2] | Op[1] & ~Op[0];
    assign op2_B = Op[2] | Op[1] & ~Op[0];
    assign cpl = ~Op[2] & ~Op[1] & Op[0];

    wire [3:0] Zero = 4'b0000;
    wire [3:0] One = 4'b0001;
    wire [3:0] Aux1;
    wire [3:0] Aux2; 
    mux2_4 mux2_41(Aux1, Zero, One, add1);
    mux2_4 mux2_42(AMod, Aux1, A, op1_A);
    mux2_4 mux2_43(Aux2, A, B, op2_B);
    compl1 compl11(BMod, Aux2, cpl);

endmodule
