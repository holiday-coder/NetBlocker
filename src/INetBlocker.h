#pragma once
#include <QString>

namespace blocker
{
class INetBlocker
{
public:
    virtual ~INetBlocker( ) = default;
    virtual void block( const QString& ip ) = 0;
    virtual void unblock( ) = 0;
};
}  // namespace blocker
