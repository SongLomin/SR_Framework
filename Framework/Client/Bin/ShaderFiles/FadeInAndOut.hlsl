

// matrix
matrix world;
matrix view;
matrix proj;

// textureCUBE

texture		g_Texture;
sampler		DefaultSampler = sampler_state 
{	
	texture = g_Texture;
    AddressU = clamp;
    AddressV = clamp;

	MINFILTER = LINEAR;
	MAGFILTER = LINEAR;
	MIPFILTER = None;	
};

//fade out Offset
float		FadeOuteOffSet = 1.f;//Set Value from outside


struct VS_IN
{
	float3 vPosition : POSITION;
	float2 vTexUV : TEXCOORD0;
};

struct VS_OUT
{
	float4 vPosition : POSITION;
	float2 vTexUV : TEXCOORD0;
};

VS_OUT VS_MAIN(/* 정점*/VS_IN In)
{
	VS_OUT		Out;

	vector		vPosition = mul(float4(In.vPosition, 1.f), world);
	vPosition = mul(vPosition, view);
	vPosition = mul(vPosition, proj);

	Out.vPosition = vPosition;
	Out.vTexUV = In.vTexUV;

	return Out;
}

/* 정점 세개에 대해서 w나누기연산. */
/* 뷰포트 변환.  */
/* 래스터라이즈한다. == 픽셀을 생성한다. */
struct PS_IN
{
	float4 vPosition : POSITION;
	float2 vTexUV : TEXCOORD0;	
};


vector PS_MAIN(PS_IN In) : COLOR0
{
	vector			vColor;

	vColor = tex2D(DefaultSampler, In.vTexUV);
	vColor.w = 1.f;	

	vColor *= FadeOuteOffSet;

	return vColor;
}

technique			DefaultTechnique
{
	pass Default
	{
		VertexShader = compile vs_3_0 VS_MAIN();
		PixelShader = compile ps_3_0 PS_MAIN();
	}
}


