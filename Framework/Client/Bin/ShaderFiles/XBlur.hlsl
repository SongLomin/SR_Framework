matrix world;
matrix view;
matrix proj;

// Foreground texture  
texture ForegroundTexture; 
// Foreground sampler  
sampler2D foreground = sampler_state {  
    texture = (ForegroundTexture);  
    MinFilter = Linear;  
    MagFilter = Linear;  
    MipFilter = Linear;  
};  
  
// Pixel width in texels  
float pixelWidth;  
  
float PixelKernel[13] =  
{  
    -6,  
    -5,  
    -4,  
    -3,  
    -2,  
    -1,  
     0,  
     1,  
     2,  
     3,  
     4,  
     5,  
     6,  
};  
  
static const float BlurWeights[13] =   
{  
    0.002216,  
    0.008764,  
    0.026995,  
    0.064759,  
    0.120985,  
    0.176033,  
    0.199471,  
    0.176033,  
    0.120985,  
    0.064759,  
    0.026995,  
    0.008764,  
    0.002216,  
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

VS_OUT VS_MAIN(/* Á¤Á¡*/VS_IN In)
{
	VS_OUT		Out;

	vector		vPosition = mul(float4(In.vPosition, 1.f), world);
	vPosition = mul(vPosition, view);
	vPosition = mul(vPosition, proj);

	Out.vPosition = vPosition;
	Out.vTexUV = In.vTexUV;


	return Out;
}

struct PS_IN
{
	float4 vPosition : POSITION;
	float2 vTexUV : TEXCOORD0;	
};

  
// Effect function  
float4 PS_Main(PS_IN In) : COLOR0  
{  
    // Apply surrounding pixels  
    float4 color = 0;  
    float2 samp = In.vTexUV;  
    samp.y = In.vTexUV.y;  
  
    for (int i = 0; i < 13; i++) {  
        samp.x = In.vTexUV.x + PixelKernel[i] * pixelWidth;  
        color += tex2D(foreground, samp.xy) * BlurWeights[i];  
    }  
  
    return color;  
}  
  
technique DefaultTechnique  
{  
    pass p0  
    {  
        VertexShader = compile vs_3_0 VS_MAIN();  
        PixelShader = compile ps_3_0 PS_Main();  
    }  
} 