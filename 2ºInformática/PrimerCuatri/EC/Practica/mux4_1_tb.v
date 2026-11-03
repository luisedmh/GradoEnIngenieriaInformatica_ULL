module mux4_1_tb;
    reg a, b, c, d;
    reg [1:0] S;
    wire out;

    // Instanciar el módulo mux4_1
    mux4_1 uut (
        .out(out),
        .a(a),
        .b(b),
        .c(c),
        .d(d),
        .S(S)
    );

    initial begin
        // Inicializar el archivo de volcado
        $dumpfile("mux4_1_tb.vcd");
        $dumpvars(0, mux4_1_tb);
        
        // Monitorear las señales
        $monitor("Time=%0t | S=%b | a=%b | b=%b | c=%b | d=%b | out=%b", $time, S, a, b, c, d, out);

        // Probar diferentes combinaciones de entradas
        a = 1'b0; b = 1'b0; c = 1'b0; d = 1'b0; S = 2'b00; #10;
        a = 1'b0; b = 1'b1; c = 1'b0; d = 1'b0; S = 2'b01; #10;
        a = 1'b0; b = 1'b0; c = 1'b1; d = 1'b0; S = 2'b10; #10;
        a = 1'b0; b = 1'b0; c = 1'b0; d = 1'b1; S = 2'b11; #10;

        // Cambiar el estado de las entradas
        a = 1'b1; b = 1'b0; c = 1'b1; d = 1'b0; S = 2'b00; #10;
        a = 1'b1; b = 1'b1; c = 1'b0; d = 1'b0; S = 2'b01; #10;
        a = 1'b1; b = 1'b0; c = 1'b1; d = 1'b1; S = 2'b10; #10;
        a = 1'b0; b = 1'b1; c = 1'b1; d = 1'b1; S = 2'b11; #10;

        // Finalizar la simulación
        $finish;
    end
endmodule
