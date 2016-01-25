//
//  Trainer.hpp
//  NumCH
//
//  Created by Christian J Howard on 1/24/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#ifndef Trainer_h
#define Trainer_h

#include "Network.hpp"
#include "DataSet.hpp"

namespace ANN {
    
    template<class Train>
    class Trainer {
    public:
        
        
        void train( Network & net, DataSet & dset ){
            static_cast<Train*>(this)->init(net);
            while( !static_cast<Train*>(this)->doneTraining() ){
                static_cast<Train*>(this)->updateNet( net, dset );
            }
        }
        
        
    };
    
    
}



#endif /* Trainer_h */
