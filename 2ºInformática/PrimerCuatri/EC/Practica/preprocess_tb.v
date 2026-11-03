`timescale 1ns / 10ps

module tb_preprocess;

    reg [3:0] A;          
    reg [3:0] B;           
    reg [2:0] Op;         
    wire [3:0] AMod;      
    wire [3:0] BMod;      

    preprocess uut (
        .AMod(AMod),
        .BMod(BMod),
        .A(A),
        .B(B),
        .Op(Op)
    );

    initial begin
        $dumpfile("tb_preprocess.vcd");
        $dumpvars(0, tb_preprocess);

        $monitor("Time=%0t | A=%b | B=%b | Op=%b | AMod=%b | BMod=%b", 
                  $time, A, B, Op, AMod, BMod);

        // Caso 1: Op = 000, se espera que AMod = 0000 y BMod = A
        A = 4'b0101; B = 4'b1010; Op = 3'b000;
        #10; // Espera de 10 unidades de tiempo

        // Caso 2: Op = 001, se espera AMod = 0001 y BMod = cmpl1(A)
        A = 4'b1100; B = 4'b0011; Op = 3'b001;
        #10;

        // Caso 3: Op = 010, se espera que AMod = A y BMod = B
        A = 4'b1111; B = 4'b0000; Op = 3'b010;
        #10;

        // Caso 4: Op = 011, AMod = 0001 y BMod = A
        A = 4'b0001; B = 4'b1110; Op = 3'b011;
        #10;

        // Caso 5: Op = 100, AMod = A y BMod = B
        A = 4'b0010; B = 4'b1101; Op = 3'b100;
        #10;

        // Caso 6: Op = 101, AMod = A y BMod = B
        A = 4'b1001; B = 4'b0110; Op = 3'b101;
        #10;

        // Caso 7: Op = 110, AMod = A y BMod = B
        A = 4'b1110; B = 4'b0001; Op = 3'b110;
        #10;

        // Caso 8: Op = 111, AMod = x y BMod = A
        A = 4'b0111; B = 4'b1000; Op = 3'b111;
        #10;

        $finish;
    end
endmodule
