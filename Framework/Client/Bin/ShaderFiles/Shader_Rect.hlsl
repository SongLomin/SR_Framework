

// matrix
float4x4			g_WorldMatrix, g_ViewMatrix, g_ProjMatrix;

texture				g_Texture;

float				g_fPower = 0.f;
// textureCUBE

sampler		DefaultSampler = sampler_state 
{	
	texture = g_Texture;
	/*ADDRESSU = WRAP;
	ADDRESSV = WRAP;*/

	MINFILTER = LINEAR;
	MAGFILTER = LINEAR;
	MIPFILTER = LINEAR;	
};



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

	vector		vPosition = mul(float4(In.vPosition, 1.f), g_WorldMatrix);
	vPosition = mul(vPosition, g_ViewMatrix);
	vPosition = mul(vPosition, g_ProjMatrix);

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


	return vColor;
}

technique			DefaultTechnique
{
	pass Default
	{

		//AlphaTestEnable = true;
		//AlphaRef = 50;
		//AlphaFunc = Greater;

		/*AlphaBlendEnable = true;
		BlendOp = Add;
		SrcBlend = SrcAlpha;
		DestBlend = InvSrcAlpha;*/

		/*CullMode = cw;*/

		VertexShader = compile vs_3_0 VS_MAIN();
		PixelShader = compile ps_3_0 PS_MAIN();

		
	}

	pass Blending
	{
		VertexShader = compile vs_3_0 VS_MAIN();
		PixelShader = compile ps_3_0 PS_MAIN();
	}
}


