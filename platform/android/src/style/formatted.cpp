#include "formatted.hpp"
#include "formatted_section.hpp"

namespace mbgl {
namespace android {

void Formatted::registerNative(jni::JNIEnv& env) {
    jni::Class<Formatted>::Singleton(env);
}

jni::Local<jni::Object<Formatted>> Formatted::New(jni::JNIEnv& env, const style::expression::Formatted& value) {
    static auto& formatted = jni::Class<Formatted>::Singleton(env);
    static auto formattedConstructor = formatted.GetConstructor<jni::Array<jni::Object<FormattedSection>>>(env);
    static auto& formattedSection = jni::Class<FormattedSection>::Singleton(env);
    static auto formattedSectionConstructor = formattedSection.GetConstructor<jni::String, double, jni::Array<jni::String>>(env);

    auto sections = jni::Array<jni::Object<FormattedSection>>::New(env, value.sections.size());
    for (std::size_t i = 0; i < value.sections.size(); i++) {
        auto section = value.sections.at(i);
        auto text = jni::Make<jni::String>(env, section.text);

        auto fontScale = 1.0;
        if (section.fontScale) {
            fontScale = section.fontScale.value();
        }

        auto fontStack = jni::Array<jni::String>::New(env, 0);
        if (section.fontStack) {
            fontStack = jni::Array<jni::String>::New(env, section.fontStack.value().size());
            for (std::size_t j = 0; j < section.fontStack.value().size(); j++) {
                fontStack.Set(env, j, jni::Make<jni::String>(env, section.fontStack.value().at(j)));
            }
        }

        sections.Set(env, i, formattedSection.New(env, formattedSectionConstructor, text, fontScale, fontStack));
    }

    return formatted.New(env, formattedConstructor, sections);
}

} // namespace android
} // namespace mbgl