#include "Core/System/SingletonInstanceControl.HPP"

#include <stdexcept>

#include <boost/interprocess/sync/named_mutex.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <boost/locale.hpp>

class SingletonInstanceControlIMPL {
    public:
        boost::interprocess::named_mutex Mutex;
        explicit SingletonInstanceControlIMPL(const std::string& InstanceID)
            : Mutex(boost::interprocess::open_or_create, InstanceID.c_str()) {
            // The real work is done in the SingletonInstanceControl constructor
        }
};

SingletonInstanceControl::SingletonInstanceControl(const std::string& InstanceID) {
    try {
        PIMPL = std::make_unique<SingletonInstanceControlIMPL>(InstanceID);
        if (!PIMPL->Mutex.try_lock()) {
            throw std::runtime_error(boost::locale::translate("Application Already Running"));
        }
    } catch (const boost::interprocess::interprocess_exception& Error) {
        std::string Message = boost::locale::translate("Unable to Create or Open Instance Lock: ");
        throw std::runtime_error(Message+ Error.what());
    }
}

SingletonInstanceControl::~SingletonInstanceControl() {
    try {
        if (PIMPL) {
            PIMPL->Mutex.unlock();
        }
    } catch (const boost::interprocess::interprocess_exception&) {

    }
}