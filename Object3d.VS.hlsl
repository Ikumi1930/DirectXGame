struct VertexShaderOutput {
	float32_t4 position : SV_POSITION;
};

struct VertexShadreInput {
	float32_t4 posotion : POSITION0;
};


VertexSharedOutput main(VertexShaderInput input) { 
	VertexShaderOutput output;
	output.position = input.position;
	return output;
}






