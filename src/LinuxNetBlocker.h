#pragma once
#include "INetBlocker.h"

namespace blocker
{
class LinuxNetBlocker : public INetBlocker
{
public:
    void block( const QString& ip ) override;
    void unblock( ) override;

private:
    bool m_is_blocked = false;
};
}  // namespace blocker
