set(KWSYS_NAMESPACE itksys)
set(KWSYS_USE_SystemTools 1)
set(KWSYS_USE_RegularExpression 1)
set(KWSYS_USE_Directory 1)
set(KWSYS_USE_Base64 1)
set(KWSYS_USE_MD5 1 )
set(KWSYS_USE_FundamentalType 1)
set(KWSYS_USE_CommandLineArguments 1)
set(KWSYS_USE_Process 1)
set(KWSYS_USE_DynamicLoader 1)
set(KWSYS_USE_Glob 1)
set(KWSYS_USE_Registry 1)
set(KWSYS_USE_SystemInformation 1)
set(KWSYS_INSTALL_INCLUDE_DIR ${ITKKWSys_INSTALL_INCLUDE_DIR})
set(KWSYS_INSTALL_LIB_DIR ${ITKKWSys_INSTALL_LIBRARY_DIR})
set(KWSYS_INSTALL_BIN_DIR ${ITKKWSys_INSTALL_RUNTIME_DIR})
set(KWSYS_INSTALL_DOC_DIR ${ITK_INSTALL_DOC_DIR})
set(KWSYS_INSTALL_EXPORT_NAME ${ITKKWSys-targets})
set(KWSYS_INSTALL_COMPONENT_NAME_RUNTIME RuntimeLibraries)
set(KWSYS_INSTALL_COMPONENT_NAME_DEVELOPMENT Development)

add_subdirectory(KWSys)
itk_module_target(${KWSYS_NAMESPACE} NO_INSTALL)
