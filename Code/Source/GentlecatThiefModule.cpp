
#include <AzCore/Memory/SystemAllocator.h>
#include <AzCore/Module/Module.h>

#include "GentlecatThiefSystemComponent.h"

namespace GentlecatThief
{
    class GentlecatThiefModule
        : public AZ::Module
    {
    public:
        AZ_RTTI(GentlecatThiefModule, "{a8dc7552-22a0-4891-b464-ed775c409a04}", AZ::Module);
        AZ_CLASS_ALLOCATOR(GentlecatThiefModule, AZ::SystemAllocator, 0);

        GentlecatThiefModule()
            : AZ::Module()
        {
            // Push results of [MyComponent]::CreateDescriptor() into m_descriptors here.
            m_descriptors.insert(m_descriptors.end(), {
                GentlecatThiefSystemComponent::CreateDescriptor(),
            });
        }

        /**
         * Add required SystemComponents to the SystemEntity.
         */
        AZ::ComponentTypeList GetRequiredSystemComponents() const override
        {
            return AZ::ComponentTypeList{
                azrtti_typeid<GentlecatThiefSystemComponent>(),
            };
        }
    };
}// namespace GentlecatThief

AZ_DECLARE_MODULE_CLASS(Gem_GentlecatThief, GentlecatThief::GentlecatThiefModule)
