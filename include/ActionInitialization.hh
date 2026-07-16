/// \file ActionInitialization.hh
/// \brief Definition of BasicDetector::ActionInitialization()

#ifndef BasicDetectorActionInitialization_h
#define BasicDetectorActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

namespace BasicDetector
{
class ActionInitialization : public G4VUserActionInitialization
{
    public:
    ActionInitialization() = default;
    ~ActionInitialization() override = default;

    void Build() const override;
    void BuildForMaster() const override;
};
}
#endif
