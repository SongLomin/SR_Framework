

// matrix
matrix world;
matrix view;
matrix proj;

// textureCUBE

float4 Color;

struct VS_IN
{
	float3 vPosition : POSITION;
};

struct VS_OUT
{
	float4 vPosition : POSITION;
};

VS_OUT VS_MAIN(/* Á¤Á¡*/VS_IN In)
{
	VS_OUT		Out;

	vector		vPosition = mul(float4(In.vPosition, 1.f), world);
	vPosition = mul(vPosition, view);
	vPosition = mul(vPosition, proj);

	Out.vPosition = vPosition;

	return Out;
}

vector PS_MAIN(VS_OUT In) : COLOR0
{
	vector			vColor;

	vColor = Color;

	return vColor;
}

technique			DefaultTechnique
{
	pass Default
	{

		VertexShader = compile vs_3_0 VS_MAIN();
		PixelShader = compile ps_3_0 PS_MAIN();

		AlphaBlendEnable = true;
		//BlendOp = ;
		SrcBlend = SrcAlpha;
		DestBlend = InvSrcAlpha;
		CullMode = None;

	}
}


