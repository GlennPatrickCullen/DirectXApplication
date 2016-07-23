////////////////////////////////////////////////////////////////////////////////
// Filename: outlinevertexshader.vs
////////////////////////////////////////////////////////////////////////////////


/////////////
// GLOBALS //
/////////////
cbuffer PerFrameBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};


//////////////
// TYPEDEFS //
//////////////
struct VertexInputType
{
    float4 position : POSITION;
    float2 tex : TEXCOORD0;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
};


////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////
PixelInputType OutlineVertexShader(VertexInputType input)
{
    PixelInputType output;
    float LineThickness = .03;
	float4 original = mul(mul(mul(input.position, worldMatrix), viewMatrix), projectionMatrix);
	float4 normal = mul(mul(mul(input.Normal, worldMatrix), viewMatrix), projectionMatrix);
	 
	// Change the position vector to be 4 units for proper matrix calculations.
    input.position.w = 1.0f;

	// Calculate the position of the vertex against the world, view, and projection matrices.
    /*output.position = mul(input.position, worldMatrix);
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectionMatrix);*/

    output.position = original + (mul(LineThickness,normal));

	// Store the texture coordinates for the pixel shader.
	output.tex = input.tex;
    
    return output;
}