//
//  observer.hpp
//  a4q4
//
//  Created by 马弘德 on 2020/3/24.
//  Copyright © 2020 Mason. All rights reserved.
//

#ifndef _OBSERVER_H_
#define _OBSERVER_H_

// DO NOT MODIFY THIS FILE!

template <typename InfoType, typename StateType> class Subject;
class Cell;

template <typename InfoType, typename StateType> class Observer {
public:
    virtual void notify(Subject<InfoType, StateType> &whoFrom) = 0; // pass the Subject that called the notify method
    virtual ~Observer() = default;
};
#endif
