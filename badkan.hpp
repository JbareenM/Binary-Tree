//
//  badkan.hpp
//  Binary_Tree
//
//  Created by Jeme Jbareen on 3/20/19.
//  Copyright © 2019 Jeme Jbareen. All rights reserved.
//

#pragma once

#define CHECK_OK(actual) check_ok([&](){actual;}, __FILE__+string(":")+to_string(__LINE__))
#define CHECK_THROWS(actual) check_throws([&](){actual;}, __FILE__+string(":")+to_string(__LINE__))
#define CHECK_EQUAL(actual,expected) check_equal([&](){return actual;}, expected, __FILE__+string(":")+to_string(__LINE__))
#define CHECK_OUTPUT(actual,expected) check_equal([&](){ostringstream ostr; ostr<<"'"<<actual<<"'"; return ostr.str();}, "'"+string(expected)+"'", __FILE__+string(":")+to_string(__LINE__))
#define CHECK_INPUT(actual,expected) check_input(actual, expected)

#include <string>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <ctime>
#include <csignal>
#include <csetjmp>
using std::string, std::ostream, std::endl, std::cerr, std::exception, std::ostringstream,  std::istringstream, std::to_string;


namespace badkan {
    
    /* The following code is used for catching signals (e.g. for timeout) during the execution. */
    jmp_buf longjmp_buffer;        // A buffer to hold info on where to jump to.
    
    void catch_signal(int signal_number) {
        longjmp (longjmp_buffer,signal_number);
    }
    
    class TestCase {
        string name;         // Name of test-case - for showing in error messages
        int passed, failed;  // Number of tests passed/failed so far.
        ostream& output;     // Stream to which the error messages will be sent.
        clock_t  start_time; // time in which the test-case is constructed.
        
    public:
        TestCase(const string& name, ostream& output=cerr):
        name(name),
        output(output),
        passed(0), failed(0),
        start_time(clock())
        {
            std::signal(SIGTERM, catch_signal);
        }
        
        int right() const { return this->passed; }
        int wrong() const { return this->failed; }
        int total() const { return failed+passed; }
        int grade() const { return (total()==0? 0: 100*passed/total()); }
        
        ostream& print(ostream& out, bool show_grade=true) const {
            double elapsed_seconds = double(clock() - start_time) / CLOCKS_PER_SEC;
            out << endl << "*** CPU time: " << elapsed_seconds << " sec.  Right: " << passed << ".  Wrong: " << failed << ". ";
            if (show_grade) out << "Grade: " << grade() << ". ";
            out << "***" << endl;
            return out;
        }
        
        TestCase& print()  {
            print(output, /*show_grade=*/true);
            return *this;
        }
        
        TestCase& print_timeout()  {
            output << "Your program timed out! (caught signal TERM)" << endl;
            print(output, /*show_grade=*/false);
            return *this;
        }
        
        
        
        /** Checks that the given function is OK, i.e., does not throw an exception */
        template<typename TFUNC> TestCase& check_ok(const TFUNC actual_func, const string& context) {
            try {
                get_actual_value<TFUNC,void>(actual_func, context);
                passed++;
            } catch(...) {}
            return *this;
        }
        
        /** Checks that the given function throws an exception */
        template<typename TFUNC> TestCase& check_throws(const TFUNC actual_func, const string& context) {
            try {
                actual_func();
                failed++;
                output << context << ", "  << title() << "There should be an exception!" << endl;
            } catch(...) {
                passed++;
            }
            return *this;
        }
        
        template<typename TFUNC, typename TVAL> TestCase& check_equal(const TFUNC actual_func, const TVAL& expected_value, const string& context) {
            try {
                TVAL actual_value = get_actual_value<TFUNC,TVAL>(actual_func, context);
                if (incorrect(actual_value==expected_value))
                    output << context << ", " << title() << "the result was " << actual_value << " but it should equal " << expected_value << "!" << endl;
            } catch(...) {}
            return *this;
        }
        
    private:
        
        string title() {
            return name + " test #" + std::to_string(total()) + ": ";
        }
        
        template<typename TFUNC, typename TVAL> TVAL get_actual_value(TFUNC actual_func, const string& context) {
            try {
                return actual_func();
            } catch (const string& message) {
                failed++;
                output << context << ", "  << title() << "There was an exception: " << message << endl;
                throw;
            } catch (const exception& ex) {
                failed++;
                output << context << ", "  << title() << "There was an exception: " << ex.what() << endl;
                throw;
            } catch (...) {
                failed++;
                output << context << ", "  << title() << "There was an exception." << endl;
                throw;
            }
        }
        
        bool incorrect(bool condition) {
            if (condition) {
                passed++;
                return false;
            } else {
                failed++;
                return true;
            }
        }
        
    }; // end class TestCase
    
}; // end namespace badkan
