

// matrix
matrix world;
matrix view;
matrix proj;

float3 Color;

texture				g_BloomTex;
sampler		DefaultSampler = sampler_state 
{	
	texture = g_BloomTex;
	/*ADDRESSU = WRAP;
	ADDRESSV = WRAP;*/

	MINFILTER = LINEAR;
	MAGFILTER = LINEAR;
	MIPFILTER = LINEAR;	
};



struct VS_IN
{
	float3 vPosition : POSITION;
};

struct VS_OUT
{
	float4 vPosition : POSITION;
};

VS_OUT VS_MAIN(/* 정점*/VS_IN In)
{
	VS_OUT		Out = (VS_OUT)0;

	vector		vPosition = mul(float4(In.vPosition, 1.f), world);
	vPosition = mul(vPosition, view);
	vPosition = mul(vPosition, proj);

	Out.vPosition = vPosition;

	return Out;
}

/* 정점 세개에 대해서 w나누기연산. */
/* 뷰포트 변환.  */
/* 래스터라이즈한다. == 픽셀을 생성한다. */
struct PS_IN
{
	float4 vPosition : POSITION;
};

struct PS_OUTPUT
{
    float4 Origin : COLOR0;
    float4 Bloom : COLOR1;
};


PS_OUTPUT PS_MAIN(PS_IN In)
{
	PS_OUTPUT			PS_out = (PS_OUTPUT)0;

	PS_out.Origin = float4(Color.xyz, 1.f);
	PS_out.Bloom =  float4(Color.xyz, 1.f);

	return PS_out;
}

technique			DefaultTechnique
{
	pass Default
	{
		VertexShader = compile vs_3_0 VS_MAIN();
		PixelShader = compile ps_3_0 PS_MAIN();
	}
}


