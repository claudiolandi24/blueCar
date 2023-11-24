#include "menuupdateuser.h"


void ActionUpdateUser::updateInDb(){
    user.updateInDb();
    QTextStream(stdout) << "User updated successfully:" << Qt::endl;
    user.printAsTable();
    printEmptyLineSeparator();
}

void ActionUpdateUsername::run(){
    user.setUsernameFromTerminal();
    updateInDb();
}

void ActionUpdatePwdHash::run(){
    user.setPwdHashFromTerminal();
    updateInDb();
}

void ActionUpdateNameOfUser::run(){
    user.setNameFromTerminal();
    updateInDb();
}

void ActionUpdateSurname::run(){
    user.setSurnameFromTerminal();
    updateInDb();
}

void ActionUpdateAddress::run(){
    user.setAddressFromTerminal();
    updateInDb();
}

void ActionUpdateCreditCard::run(){
    user.setCreditCardFromTerminal();
    updateInDb();
}

void ActionUpdateDrivingLicense::run(){
    user.setDrivingLicenseFromTerminal();
    updateInDb();
}

MenuUpdateUser::MenuUpdateUser(string label_, User user_) : Menu(label_)
{
    user=user_;
    
    title="UPDATE USER";
    //addItem(make_unique<ActionUpdateUsername>("Update the ", user));
    //addItem(make_unique<ActionUpdate>("Update the ", user));
}
