#ifndef JSTUDIO_CONTROL_H
#define JSTUDIO_CONTROL_H

#include "JSystem/JStudio/JStudio/fvb.h"
#include "JSystem/JStudio/JStudio/stb.h"
#include "dolphin/gx.h"
#include "dolphin/mtx.h"

namespace JStudio {
    struct TObject;
    struct TCreateObject {
        TCreateObject() {}
        virtual ~TCreateObject() = 0;
        virtual bool create(TObject**, JStudio::stb::data::TParse_TBlock_object const&) = 0;

        /* 0x4 */ JGadget::TLinkListNode mNode;
    }; // Size: 0xC

    struct TFactory : public stb::TFactory {
        TFactory() {}

        virtual ~TFactory();
        virtual TObject* create(JStudio::stb::data::TParse_TBlock_object const&);

        void appendCreateObject(JStudio::TCreateObject*);

        /* 0x04 */ JGadget::TLinkList<TCreateObject, -4> mList;
        /* 0x10 */ fvb::TFactory fvb_Factory;
    };

    class TControl : public stb::TControl {
      public:
        struct TTransform_position {
            Vec mPosition;
        };
        struct TTransform_position_direction {};
        struct TTransform_translation_rotation {};
        struct TTransform_translation_rotation_scaling {};

        TControl();
        virtual ~TControl();
        void transformOnSet_setOrigin(const Vec&, f32);
        void transformOnGet_setOrigin(const Vec&, f32);

        void setFactory(JStudio::TFactory* factory) {
            stb::TFactory* stb_factory = factory;
            fvb::TFactory* fvb_factory = factory == NULL ? NULL : &factory->fvb_Factory;
            stb::TControl::setFactory(stb_factory);
            fvb_Control.setFactory(fvb_factory);
        }

        void stb_destroyObject_all() { stb::TControl::destroyObject_all(); }
        void fvb_destroyObject_all() { fvb_Control.destroyObject_all(); }

        void destroyObject_all() {
            stb_destroyObject_all();
            fvb_destroyObject_all();
        }

        bool transformOnSet_isEnabled() const { return mTransformOnSet; }
        void transformOnSet_enable(bool param_0) { mTransformOnSet = param_0; }
        bool transformOnGet_isEnabled() const { return mTransformOnGet; }
        void transformOnGet_enable(bool param_0) { mTransformOnGet = param_0; }

        void transform_enable(bool param_0) {
            transformOnGet_enable(param_0);
            transformOnSet_enable(param_0);
        }

        void transform_setOrigin(const Vec& xyz, f32 rotY) {
            transformOnGet_setOrigin(xyz, rotY);
            transformOnSet_setOrigin(xyz, rotY);
        }

        f32 transformOnSet_getRotationY() const { return mTransformOnSet_RotationY; }
        CMtx44Ptr transformOnSet_getMatrix() const { return mTransformOnSet_Matrix; }
        CMtx44Ptr transformOnGet_getMatrix() const { return mTransformOnGet_Matrix; }

        void setSecondPerFrame(f64 param_0) { mSecondPerFrame = param_0; }
        f64 getSecondPerFrame() const { return mSecondPerFrame; }

        fvb::TObject* fvb_getObject(const void* param_1, u32 param_2) {
            return fvb_Control.getObject(param_1, param_2);
        }

        fvb::TObject* fvb_getObject_index(u32 index) { return fvb_Control.getObject_index(index); }

        TFunctionValue* getFunctionValue(const void* param_1, u32 param_2) {
            fvb::TObject* obj = fvb_getObject(param_1, param_2);
            if (obj == NULL) {
                return NULL;
            }
            return obj->referFunctionValue();
        }

        TFunctionValue* getFunctionValue_index(u32 index) {
            fvb::TObject* obj = fvb_getObject_index(index);
            if (obj == NULL) {
                return NULL;
            }
            return obj->referFunctionValue();
        }

        void fvb_getObjectContainer() const {}
        void fvb_referControl() {}
        void fvb_removeObject_all() {}
        void stb_getObjectContainer() const {}
        void stb_referObjectContainer() {}
        void stb_removeObject(JStudio::TObject*) {}
        void transformOnGet_transform(const JStudio::TControl::TTransform_position&,
                                      JStudio::TControl::TTransform_position*) const {}
        void transformOnGet_transform(const JStudio::TControl::TTransform_position_direction&,
                                      JStudio::TControl::TTransform_position_direction*) const {}
        void transformOnGet_transform(const JStudio::TControl::TTransform_translation_rotation&,
                                      JStudio::TControl::TTransform_translation_rotation*) const {}
        void transformOnGet_transformDirection(const Vec&, Vec*) const {}
        void transformOnGet_transformRotation(const Vec&, Vec*) const {}
        void transformOnGet_transformTranslation(const Vec&, Vec*) const {}
        void transformOnGet_transform_ifEnabled(const JStudio::TControl::TTransform_position_direction&,
                                                JStudio::TControl::TTransform_position_direction*) const {}
        void transformOnGet_transform_ifEnabled(const JStudio::TControl::TTransform_translation_rotation&,
                                                JStudio::TControl::TTransform_translation_rotation*) const {}
        void transformOnSet_transform(const JStudio::TControl::TTransform_position&,
                                      JStudio::TControl::TTransform_position*) const {}
        void transformOnSet_transform(const JStudio::TControl::TTransform_position_direction&,
                                      JStudio::TControl::TTransform_position_direction*) const {}
        void transformOnSet_transform(const JStudio::TControl::TTransform_translation_rotation&,
                                      JStudio::TControl::TTransform_translation_rotation*) const {}
        void transformOnSet_transform(CMtx44Ptr, Mtx44Ptr) const {}
        void transformOnSet_transformDirection(const Vec&, Vec*) const {}
        void transformOnSet_transformDirection_ifEnabled(const Vec&, Vec*) const {}
        void transformOnSet_transformRotation(const Vec&, Vec*) const {}
        void transformOnSet_transformTranslation(const Vec&, Vec*) const {}
        void transformOnSet_transformTranslation_ifEnabled(const Vec&, Vec*) const {}
        void transformOnSet_transform_ifEnabled(const JStudio::TControl::TTransform_position_direction&,
                                                JStudio::TControl::TTransform_position_direction*) const {}
        void transformOnSet_transform_ifEnabled(const JStudio::TControl::TTransform_translation_rotation&,
                                                JStudio::TControl::TTransform_translation_rotation*) const {}
        void transformOnSet_transform_ifEnabled(CMtx44Ptr, Mtx44Ptr) const {}

        /* 0x58 */ f64 mSecondPerFrame;
        /* 0x60 */ fvb::TControl fvb_Control;
        /* 0x74 */ bool mTransformOnSet;
        /* 0x75 */ bool mTransformOnGet;
        /* 0x78 */ Vec field_0x8c;
        /* 0x84 */ Vec field_0x98;
        /* 0x90 */ f32 mTransformOnSet_RotationY;
        /* 0x94 */ f32 field_0xa8;
        /* 0x98 */ Mtx mTransformOnSet_Matrix;
        /* 0xC8 */ Mtx mTransformOnGet_Matrix;
    };

    struct TParse : public stb::TParse {
        TParse(JStudio::TControl*);
        bool parseBlock_block_fvb_(JStudio::stb::data::TParse_TBlock const&, u32);

        virtual ~TParse();
        virtual bool parseHeader(JStudio::stb::data::TParse_THeader const&, u32);
        virtual bool parseBlock_block(JStudio::stb::data::TParse_TBlock const&, u32);

        TControl* getControl() { return (TControl*)stb::TParse::getControl(); }

        /* 0x04 */ fvb::TParse field_0x04;
    };

}; // namespace JStudio

#endif /* JSTUDIO_CONTROL_H */
