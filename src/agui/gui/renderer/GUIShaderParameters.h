#pragma once

#include <string>
#include <unordered_map>

#include <agui/agui.h>
#include <agui/gui/renderer/GUIShaderParameter.h>

using std::string;
using std::to_string;
using std::unordered_map;

/**
 * TDME2 engine entity shader parameters
 * @author Andreas Drewke
 */
class agui::gui::renderer::GUIShaderParameters final
{
private:
	unordered_map<string, GUIShaderParameter> parameters;
	string shaderId;

	mutable string hash;
	mutable bool changed { false };

	/**
	 * Compute shader parameters hash
	 */
	void computeHash();

public:
	/**
	 * Public constructor
	 */
	GUIShaderParameters() {
	}

	/**
	 * Destructor
	 */
	~GUIShaderParameters() {
	}

	/**
	 * Set shader
	 * @param shaderId shader id
	 */
	void setShader(const string& shaderId) {
		if (this->shaderId == shaderId) return;
		parameters.clear();
		hash = shaderId + ";";
		changed = false;
		this->shaderId = shaderId;
	}

	/**
	 * Returns shader parameter for given parameter name, if the value does not exist, the default will be returned
	 * @param shaderId shader id
	 * @param parameterName parameter name
	 * @returns shader parameter
	 */
	const GUIShaderParameter getShaderParameter(const string& parameterName) const;

	/**
	 * Set shader parameter for given parameter name
	 * @param shaderId shader id
	 * @param parameterName parameter name
	 * @param paraemterValue parameter value
	 */
	void setShaderParameter(const string& parameterName, const GUIShaderParameter& parameterValue);

	/**
	 * Set shader parameter for given parameter name
	 * @param shaderId shader id
	 * @param parameterName parameter name
	 * @param paraemterValue parameter value
	 */
	void setShaderParameter(const string& parameterName, const string& parameterValueString);

	/**
	 * @returns shader parameters hash
	 */
	const string& getShaderParametersHash() const {
		if (changed == true) {
			// TODO: md5 or something
			hash = shaderId + ";";
			for (const auto& [parameterName, parameterValue]: parameters) {
				switch (parameterValue.getType()) {
					case GUIShaderParameter::TYPE_NONE:
						break;
					case GUIShaderParameter::TYPE_BOOLEAN:
						hash+= to_string(parameterValue.getBooleanValue());
						break;
					case GUIShaderParameter::TYPE_INTEGER:
						hash+= to_string(parameterValue.getIntegerValue());
						break;
					case GUIShaderParameter::TYPE_FLOAT:
						hash+= to_string(static_cast<int>(parameterValue.getFloatValue() * 100.0f));
						break;
					case GUIShaderParameter::TYPE_VECTOR2:
						{
							const auto& shaderParameterArray = parameterValue.getVector2Value().getArray();
							for (auto i = 0; i < shaderParameterArray.size(); i++) {
								if (i != 0) hash+= ",";
								hash+= to_string(static_cast<int>(shaderParameterArray[i] * 100.0f));
							}
						}
						break;
					case GUIShaderParameter::TYPE_VECTOR3:
						{
							const auto& shaderParameterArray = parameterValue.getVector3Value().getArray();
							for (auto i = 0; i < shaderParameterArray.size(); i++) {
								if (i != 0) hash+= ",";
								hash+= to_string(static_cast<int>(shaderParameterArray[i] * 100.0f));
							}
						}
						break;
					case GUIShaderParameter::TYPE_VECTOR4:
					case GUIShaderParameter::TYPE_COLOR4:
						{
							const auto& shaderParameterArray = parameterValue.getVector4Value().getArray();
							for (auto i = 0; i < shaderParameterArray.size(); i++) {
								if (i != 0) hash+= ",";
								hash+= to_string(static_cast<int>(shaderParameterArray[i] * 100.0f));
							}
						}
						break;
					default:
						break;
				}
				hash+= ";";
			}
			changed = false;
		}
		return hash;
	}
};
