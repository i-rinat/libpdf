set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_library(pdf SHARED
    chunk_stream.cc
    document_loader.cc
    draw_utils.cc
    out_of_process_instance.cc
    paint_aggregator.cc
    paint_manager.cc
    pdf.cc
    pdfium/pdfium_api_string_buffer_adapter.cc
    pdfium/pdfium_assert_matching_enums.cc
    pdfium/pdfium_engine.cc
    pdfium/pdfium_mem_buffer_file_read.cc
    pdfium/pdfium_mem_buffer_file_write.cc
    pdfium/pdfium_page.cc
    pdfium/pdfium_range.cc
    preview_mode_client.cc
)

target_link_libraries(pdf ppapi_cpp)
target_link_libraries(pdf pdfium)
target_link_libraries(pdf v8)
target_link_libraries(pdf base)
target_link_libraries(pdf net)
target_link_libraries(pdf printing)

target_link_libraries(pdf ${REQ_LIBRARIES})
