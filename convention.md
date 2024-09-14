# Conventions

* header file:
    ```
        #ifndef FLS_HEADER_HPP
        #define FLS_HEADER_HPP
         
        namespace fastlanes {
        /*--------------------------------------------------------------------------------------------------------------------*/
        class ForwardDeclared;
        /*--------------------------------------------------------------------------------------------------------------------*/
        class Header {
        };
        
        } // namespace fastlanes
        #endif // FLS_HEADER_HPP
    ```
* rules:
    * no struct! always class.
    * no pragma! include header.
    *
* __Naming convention__
    * m_* -> member
    * *_t -> type
    * n_*-> number of
    * *_p -> raw ptr
    * *_up -> unique_ptr
    * *_sp -> shared_ptr
    * *_stp -> single_thread_ptr
    * *_s -> string
    * *_sz -> size
    * *_bsz -> size
    * *_md -> metadata
    * *_o -> offset
    * *_v -> value
    * *_arr -> C-arr
    * *_vec -> std::vec
    * *_idx -< index
    * *_krl -> kernel
    * *_trd -> cpu thread
    * __Can be combined__
    * *_c_p -> pointer to a counter

* __3 word system!__
    * tab -> table
    * dat -> data
    * col -> column
    * arr -> array
    * idx -> index
    * cor -> core
    * cmn -> common
    * psr -> parser
    * prm -> primitive
    * stt -> statistic
    * lmt -> limit

* __Alias__
    * sp -> std::shared_pointer<T>
    * up -> std::unique_pointer<T>
    * count-t -> uint64_t

* __Type Name__
    * T -> t
    * AT -> arrow type
    * PT -> parquet type, physical type
    *


* __Class Layout__ (0.0.1)
    ```c++
      template <typename T>
      class Class {
                  /* PUBLIC: */
      public:     /* Constructors */
  	    Class(const Class&)             = delete;
	    Class& operator=(const Class&)  = delete;
	    Class(const Class&&)            = delete;
	    Class& operator=(const Class&&) = delete;

      public:     /* Member functions */
      public:     /* Members */
            
                  /* PROTECTED: */
      protected:  /* Constructors */
      protected:  /* Member Functions */
      protected:  /* Members */
            
                  /* PRIVATE: */
      private:    /* Constructors */
      private:    /* Member Functions */
      private:    /* Members */
      };
    ```
    * ```I``` before a class name ```means``` an Interface class
    * maybe more structure?
      ```c++
        class C {
        C(const C&) = default;
        C(C&&) = default;
        C& operator=(const C&) & = default;
        C& operator=(C&&) & = default;
        virtual ~C() { }
        };
      ```

* __Comment Tag__
    * [op] -> optimization opportunity
    * [fixme] -> fixme later
    * [todo] -> todo


* __Comment Block__
  ```c++

  /*--------------------------------------------------------------------------------------------------------------------*\
   * Implementation
  \*--------------------------------------------------------------------------------------------------------------------*/
  
  ```

  ```cmake
  
  Options
  # Options: -------------------------------------------------------------------------------------------------------------
  
  ```
* __Single Line Delimitor__

  ```c++
  /*--------------------------------------------------------------------------------------------------------------------*/
  ```


* __Log__
  ```c++
  FLS_LOG_1MSG(" MY MESSAGE !")
  ```

* __Forward declare__
  ```c++
  /*--------------------------------------------------------------------------------------------------------------------*/
  class FastLanes;
  /*--------------------------------------------------------------------------------------------------------------------*/
  ```
  
