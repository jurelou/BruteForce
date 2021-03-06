/**
    @author Louis JURCZYK
    @version 1.0 10/03/19
*/

#ifndef         _ARGPARSE_HPP_
#define         _ARGPARSE_HPP_

#include		<iostream>
#include		<vector>
#include		<map>
#include 		<list>
#include 		<iostream>
#include 		<tuple>

struct Rules
{
    std::string shortName;
    std::string name;
    size_t      nbArgs;
    std::string info;
    bool        optional;
    std::string mandatoryOptions;
};

std::ostream&  operator<<(std::ostream& out, const Rules& r) {
    out <<  r.shortName<< ", " << r.name << '\t' << r.info;
    return out;
}

typedef std::tuple<std::string, std::list<std::string>> stringMap;
typedef std::map<std::string, std::vector<std::string>> dict;
class argumentParser
{
public:
    argumentParser(int ac, const char **av) {
        _args.push_back(stringMap(av[0],{}));
        _progName = av[0];
        for (size_t i = 1 ; i < ac; i++) {
            if ((std::string(av[i]).size() >= 2) && ((av[i][0] == '-') || (av[i][0] == '-' && av[i][1] == '-')))
                _args.push_back(stringMap(av[i],{}));
            else
                std::get<1>(_args.back()).push_back(av[i]);
        }
    }
    ~argumentParser() {}

    void    addArgument(const std::string& shortname, \
                const std::string& name, \
                size_t nbArgs, \
                const std::string& info, \
                bool optional = true, \
                const std::string &mandatoryOptions = "") {
        Rules item;
        item.shortName = shortname;
        item.name = name;
        item.nbArgs = nbArgs;
        item.info = info;
        item.optional = optional;
        item.mandatoryOptions = mandatoryOptions;
        _rules.push_back(item);
    }

    void        printHelp(const std::string& msg){
        std::cerr << msg <<std::endl;
        std::cerr <<"Mandatory arguments:"<<std::endl;
        for (auto i: _rules) {
            if (!i.optional && i.mandatoryOptions == ""){
                std::cout << i <<std::endl;
                for (auto a: _rules)
                    if (a.mandatoryOptions == i.name)
                        std::cout << "  -> "<<a <<std::endl;
            }
        }
        std::cerr <<std::endl<<"Optional arguments:"<<std::endl;
        for (auto i: _rules) {
            if (i.optional)
                std::cout << i <<std::endl;
        }
        exit(1);
    }

    void        parse(){
        std::vector<std::string>    m = {"-m", "--mode"};
        std::vector<std::string>    c = {"-c", "--crack"};
        std::string     mode, crack;
        bool    mandatoryFieldIsPresent;

        for (auto i: _rules){
            mandatoryFieldIsPresent = false;
            for (auto arg : _args) {
                if (std::get<0>(arg) == i.name || std::get<0>(arg) == i.shortName) {
                    mandatoryFieldIsPresent = true;
                    if (i.nbArgs > std::get<1>(arg).size())
                        printHelp("Option " + std::get<0>(arg) + " requires " + std::to_string(i.nbArgs) + " param(s)");
                }
                for (auto state : m)
                    mode = std::get<0>(arg) == state ? std::get<1>(arg).front() : mode;
                for (auto state : c)
                    crack = std::get<0>(arg) == state ? std::get<1>(arg).front(): crack;
            }
            if  (!mandatoryFieldIsPresent && !i.optional)
                printHelp("Missing a mandatory parameter: " + i.name);
        }
        for (auto i: _rules) {
            mandatoryFieldIsPresent = false;
            if (i.mandatoryOptions == mode || i.mandatoryOptions == crack){
                for (auto arg : _args)
                    mandatoryFieldIsPresent =  (std::get<0>(arg) == i.name || std::get<0>(arg) == i.shortName) ? true: mandatoryFieldIsPresent;
                if (!mandatoryFieldIsPresent)
                    printHelp("The option " + i.name + " is required when using the option " + i.mandatoryOptions);
            }
        }
    }

    bool        hasKey(const std::string& name){
        for (auto r: _rules)
            if (r.name == name || r.shortName == name)
                for(auto i : _args)
                    if (std::get<0>(i) == r.name || std::get<0>(i) == r.shortName)
                        return true;
                return false;
    }

    dict  getOptions() {
        dict  res;
        std::string name;

        for (auto i: _args) {
            for (auto r: _rules)
                res[(std::get<0>(i) == r.name || std::get<0>(i) == r.shortName) ? r.name : std::get<0>(i)] = {};
            for (auto p: std::get<1>(i))
                res[std::get<0>(i)].push_back(p);
        }
        return res;
    }
private:
    std::list<Rules>            _rules;
    std::list<stringMap>        _args;
    std::string                 _progName;
};

#endif      /*_ARGPARSE_HPP_*/