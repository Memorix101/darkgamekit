float2 InvViewSize;

texture background < string Name=""; >;	

sampler2D background_smp = sampler_state 
{
	Texture = <background>;
	AddressU = Clamp; AddressV = Clamp;
	MinFilter = Linear; MagFilter = Linear; MipFilter = None;
};

struct output
{
	float4 opos    : POSITION;  
 	float2 uv      : TEXCOORD0;  
};

output VS( float4 pos : POSITION )
{
	output OUT;

	OUT.uv = pos.xy * float2(0.5,-0.5) + 0.5;
	pos.xy = pos.xy + float2( -InvViewSize.x, InvViewSize.y );
	OUT.opos = pos;

	return OUT;	
}

float4 PS(output IN) : COLOR
{
	return tex2D(background_smp,IN.uv);
}
  
technique screenquad
{
	pass p0
	{		
		VertexShader = compile vs_2_0 VS();
		PixelShader  = compile ps_2_0 PS();	
	}
}

