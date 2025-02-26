#shader vertex
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	FragPos = vec3(model * vec4(aPos, 1.0));
	Normal = mat3(transpose(inverse(model))) * aNormal;
	TexCoords = aTexCoords;

	gl_Position = projection * view * vec4(FragPos, 1.0);
}


#shader fragment
#version 330 core

struct Material {
	sampler2D specular;
	sampler2D diffuse;
	sampler2D emission;
	float shininess;
};

struct Light {
	vec3 position;
	vec3 direction;
	float cutOff;
	float outerCutOff;

	sampler2D design;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;

};


out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

//uniform vec3 lightPos;
              
uniform vec3 viewPos;
uniform Material material;
uniform Light light;
uniform float time;

void main()
{
	
	float distance = length(light.position - FragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance*distance));


	vec3 lightDir = normalize(light.position - FragPos);
	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon = (light.cutOff - light.outerCutOff);
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
	

	// ambient
	vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;

	// diffuse 
	vec3 norm = normalize(Normal);

	

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;

	// specular
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;

	//Emission 
	vec3 emission = vec3(0.0);
	if (texture(material.specular, TexCoords).r == 0.0)   /*rough check for blackbox inside spec texture */
	{
		//apply emission texture 
		emission = texture(material.emission, TexCoords).rgb;

		//some extra fun stuff with "time uniform" 
		emission = texture(material.emission, TexCoords + vec2(0.0, time)).rgb;   /*moving */
		emission = emission * (sin(time) * 0.5 + 0.5) * 2.0;                     /*fading */
	}

	//intensity = inverse(-intensity);
	diffuse *= intensity;
	specular *= intensity;

	
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	vec3 result = (ambient + diffuse + specular + emission);
	FragColor = vec4(result, 1.0);
	
}