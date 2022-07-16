// matrix
matrix world;
matrix view;
matrix proj;



float				blurWidth;
// textureCUBE

texture		g_Texture;
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
	vector			vColor = vector(0.f, 0.f, 0.f, 0.f);

	float fBlurStart = 1.f;
	float2 center = float2(0.5f, 0.5f);//중심점<-마우스의 위치를 받아오면 마우스를 중심으로 블러됨

	In.vTexUV.xy -= center;

	float fPrecompute = blurWidth * (1.0f / 19.f);

	for (int i = 0; i < 20; ++i)
	{
		float scale = fBlurStart + (float(i) * fPrecompute);
		float2 uv = In.vTexUV.xy * scale + center;

		if (0.f > uv.x)
			uv.x = 0.f;
		else if (1.f < uv.x)
			uv.x = 1.f;

		if (0.f > uv.y)
			uv.y = 0.f;
		else if (1.f < uv.y)
			uv.y = 1.f;

		vColor += tex2D(DefaultSampler, uv);
	}

	vColor /= 20.f;

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


