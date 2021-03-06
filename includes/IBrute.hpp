/**
    @author Louis JURCZYK
    @version 1.0 08/03/19
*/

#ifndef         _IBRUTE_HPP_
#define         _IBRUTE_HPP_

#include        "ICracker.hpp"
#include        "benchMark.hpp"
#include        <iostream>
#include        <memory>


typedef std::map<std::string, std::vector<std::string>> dict;

class   IBrute
{
public:
    IBrute() :_nbTries(0), 
        _finished(false),
        _bench(std::make_shared<benchMark>())
         {}

    ~IBrute() {}

    virtual bool    	brute(void) = 0;
    virtual bool        configure(dict& options) = 0;

    void			setCracker(std::shared_ptr<ICracker> c) {
    	_cracker = c;
    }

    void                stop(){
        _finished = true;
        _bench->stop(_nbTries);
    }

protected:

    void        _update() { _nbTries++; }
    void        _start() { _bench->start(); }
    bool        _finish() {  _bench->stop(_nbTries); }
	std::shared_ptr<ICracker>   _cracker;
    unsigned long long          _nbTries;
    bool                        _finished;
private:
    std::shared_ptr<benchMark>  _bench;
};
#endif      /*_IBRUTE_HPP_*/