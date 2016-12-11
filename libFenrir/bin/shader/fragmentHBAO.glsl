#version 410

in vec2 texture_coordinates;

uniform sampler2D depth_texture;
uniform sampler2D noise_texture;
uniform sampler2D normals_texture;

uniform float zNear;
uniform float zFar;

uniform float FOV;

uniform float screenHeight;

uniform mat4 proj;
uniform float aspectRatio;

//Cor final do fragmento
layout(location=0) out vec4 hbao_colour;

const float PI = 3.14159265;

float TanToSin(float x)
{
	return x * inversesqrt(x*x + 1.0);
}
  
float LinearizeDepth(float depth) 
{
    float z = depth * 2.0 - 1.0; // Back to NDC 
    return (2.0 * zNear) / (zFar + zNear - z * (zFar - zNear));	
}

float hbao(in vec2 origin)
{
	float lastHeight = 0;
	float lastAO = 0;
	float AO = 0;
	
	//Constants
	float sampleDirection = 8;
	int sampleSteeps = 4;
	float sampleRange = 0.01;
	float kernelSize = 8.0;
	
	//Depth at origin point
	float originDepth = LinearizeDepth(texture(depth_texture, origin).r);
	vec2 textSize = textureSize(depth_texture, 0);
	
	float tanHalfFov = tan(FOV*0.5);
	vec2 ndcOriginUV = vec2(origin.x * 2.0 - 1.0, origin.y * 2.0 - 1.0);
	vec3 originViewRay = vec3(ndcOriginUV.x * tanHalfFov * aspectRatio, ndcOriginUV.y * tanHalfFov, 1.0);
	vec3 viewspaceOrigin = originViewRay*originDepth;
	
	//Origin Normal
	vec3 normal = (texture(normals_texture, origin).rgb*2.0-vec3(1.0));
	
	//Sample direction
	vec2 dir;
	
	//Distance to sample
	float sampleDistance;
	
	//Sample height from origin point
	float sampleHeight;
	
	//Horizontal Vector
	vec3 horizon;
	
	if(texture(depth_texture, origin).r == 1)
	{
		AO = 1;
	}
	else
	{
		for(int d = 0; d < sampleDirection; d++)
		{
			dir = vec2(cos(d*PI/sampleDirection), sin(d*PI/sampleDirection));
			dir *= kernelSize/sampleSteeps;
			
			vec2 uvDir = vec2((dir).x/textSize.x, (dir).y/textSize.y);
			
			vec2 sampleCoords = origin;
			
			vec3 tangent = normalize(cross(vec3(0,0,1),normal));
			vec3 bitangent = normalize(cross(normal, tangent));
			mat3 TBN = mat3(tangent, bitangent, normal);
			
			lastHeight = 0;
			lastAO = 0;
			
			for(int s = 1; s <= sampleSteeps; s++)
			{
				//Direction in textures dimensions [0,1]
				sampleCoords += uvDir;
				
				float sampleDepth = LinearizeDepth(texture(depth_texture, sampleCoords).r);
				sampleHeight = (originDepth - sampleDepth);
				
				vec2 ndcSampleUV = vec2(sampleCoords.x * 2.0 - 1.0, sampleCoords.y * 2.0 - 1.0);
				vec3 sampleViewRay = vec3(ndcSampleUV.x * tanHalfFov * aspectRatio, ndcSampleUV.y * tanHalfFov, 1.0);
				vec3 viewspaceSample = sampleViewRay*sampleDepth;
				
				//Get horizon vector
				vec3 viewspaceDirection = -(viewspaceSample - viewspaceOrigin);
				horizon = TBN * vec3(viewspaceDirection.xy, 0);
				float lenghtXY = length(horizon.xy);
				sampleDistance = length(vec3(dir*s, sampleHeight));				
				
				if(length(viewspaceDirection) <= sampleRange)
				{
					if(sampleHeight > lastHeight)
					{
						float currentAO = TanToSin(sampleHeight/length(dir*s)) - TanToSin(horizon.z/length(dir*s));
						
						AO += (1-pow(length(dir*s)/kernelSize, 2))*(currentAO-lastAO);
						
						lastHeight = sampleHeight;
						lastAO = currentAO;
					}
				}
			}
		}
		
		AO /= sampleDirection;
	
		float AOStrenght = 1000.0f;
		
		AO *= AOStrenght;
	}
	
	return (1-AO);
}

void main() {
	
	vec2 originCoords = vec2(texture_coordinates.x, texture_coordinates.y);
	hbao_colour =  vec4(vec3(hbao(originCoords)), 1.0);

	//hbao_colour = texture(normals_texture, vec2(texture_coordinates.x, texture_coordinates.y));
};