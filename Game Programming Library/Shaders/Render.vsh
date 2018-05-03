float4x4 world_view_projection : WORLDVIEWPROJECTION : register(c0);

struct Vertex
{
	float4 position : POSITION0;
	float4 color : COLOR0;
	float2 texture_coordinate : TEXCOORD0;
};

Vertex MainBasic(Vertex vertex_input)
{
    Vertex vertex_output = (Vertex) 0;

	//Multiplicando a posi��o com a matriz que cont�m os valores de World View Projection j� multiplicados e transformando a posi��o para o Screen Space
	vertex_output.position = mul(float4(vertex_input.position),world_view_projection);

	vertex_output.color = vertex_input.color;

	return vertex_output;
}

Vertex MainTexture(Vertex vertex_input)
{
	Vertex vertex_output = MainBasic(vertex_input);

	//Obtendo as coordenadas da textura antes de passar para a pr�xima fase
	vertex_output.texture_coordinate = vertex_input.texture_coordinate;

    return vertex_output;
}