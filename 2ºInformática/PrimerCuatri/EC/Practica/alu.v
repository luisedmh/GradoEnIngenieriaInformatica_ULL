module alu(output wire [3:0] R, output wire zero, carry, sign, input wire [3:0] A, B, input wire c_in, input wire [2:0] Op);

    wire [3:0] AMod;
    wire [3:0] BMod;
    preprocess preprocess1(AMod, BMod, A, B, Op);

    wire [3:0] Aux1;
    sum4_v2 sum4_v21(Aux1, carry, AMod, BMod, c_in);

    wire [3:0] Aux2;
    wire [1:0] S = Op[1:0];
    ul4 ul41(Aux2, AMod, BMod, S);

    mux2_4 mux2_41(R, Aux1, Aux2, Op[2]);

    assign zero = (R == 4'b0000);
    assign sign = R[3];

endmodule