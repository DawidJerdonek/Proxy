/// <summary>
/// Proxy Pattern
/// Idea is to pass a proxy system/whatever class or functions rather than passing the real thing.
/// Use secondary system with Proxy as an interface
/// Safer and more editable, easy to undestand but quite complex and limited uses
/// </summary>

#include <iostream>

/// <summary>
/// System used for proxy instead of using the true system class
/// </summary>
class SystemWithProxy
{
public:
	virtual void requestAccess() const = 0;
};

/// <summary>
/// Issues can be solved without editing this real system
/// </summary>
class System : public SystemWithProxy
{
public:
	void requestAccess() const override 
	{
		std::cout << "System processing information for access request" << std::endl;
	}
};

//Proxy will keep all the system information private
class Proxy : public SystemWithProxy
{
private:
	System* trueSystem;

	bool checkPermissions() const 
	{
		std::cout << "Checking Permissions before a permission request is created" << std::endl;
		return true;
	}
	void rememberRequest() const 
	{
		std::cout << "Logged the request" << std::endl;
	}

public:
	Proxy(System* t_trueSystem) : trueSystem(new System(*t_trueSystem))
	{
	}
		void requestAccess() const override
		{
			if (this->checkPermissions())
			{
				this->trueSystem->requestAccess();
				this->rememberRequest();
			}
		}

		~Proxy()
		{
			delete trueSystem;
		}

};

void client(const SystemWithProxy &t_systemWithProxy)
{
	t_systemWithProxy.requestAccess();
}

/// <summary>
/// main
/// </summary>
int main()
{
	std::cout << "Direct System Usage" << std::endl;
	System* trueSystem = new System;
	client(*trueSystem);

	std::cout << " " << std::endl;

	std::cout << "Proxy Use" << std::endl;
	Proxy* proxy = new Proxy(trueSystem);
	client(*proxy);

	return 0; 
}

