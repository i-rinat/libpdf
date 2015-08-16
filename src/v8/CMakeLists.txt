include_directories(.)

# add_definitions(-DV8_USE_EXTERNAL_STARTUP_DATA)

set(v8_library_files
    src/macros.py src/messages.h src/runtime.js src/v8natives.js src/symbol.js src/array.js
    src/string.js src/uri.js src/math.js src/third_party/fdlibm/fdlibm.js src/date.js
    src/regexp.js src/arraybuffer.js src/typedarray.js src/generator.js src/object-observe.js
    src/collection.js src/weak-collection.js src/collection-iterator.js src/promise.js
    src/messages.js src/json.js src/array-iterator.js src/string-iterator.js src/debug-debugger.js
    src/mirror-debugger.js src/liveedit-debugger.js src/templates.js src/i18n.js
)

set(v8_experimental_library_files
    src/macros.py src/messages.h src/proxy.js src/generator.js src/harmony-array.js
    src/harmony-array-includes.js src/harmony-tostring.js src/harmony-typedarray.js
    src/harmony-regexp.js src/harmony-reflect.js src/harmony-spread.js src/harmony-object.js
)

set(v8_extra_library_files
)

set(LIBRARIES_CC "${CMAKE_CURRENT_BINARY_DIR}/libraries.cc")
set(EXPERIMENTAL_LIBRARIES_CC "${CMAKE_CURRENT_BINARY_DIR}/experimental-libraries.cc")
set(EXTRA_LIBRARIES_CC "${CMAKE_CURRENT_BINARY_DIR}/extra-libraries.cc")

add_custom_command(
    OUTPUT "${LIBRARIES_CC}"
    DEPENDS ${v8_library_files}
    COMMAND python
    ARGS "${CMAKE_CURRENT_SOURCE_DIR}/tools/js2c.py" "${LIBRARIES_CC}" "CORE" ${v8_library_files}
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    VERBATIM
)

add_custom_command(
    OUTPUT "${EXPERIMENTAL_LIBRARIES_CC}"
    DEPENDS ${v8_experimental_library_files}
    COMMAND python
    ARGS "${CMAKE_CURRENT_SOURCE_DIR}/tools/js2c.py" "${EXPERIMENTAL_LIBRARIES_CC}" "EXPERIMENTAL"
         ${v8_experimental_library_files}
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    VERBATIM
)

add_custom_command(
    OUTPUT "${EXTRA_LIBRARIES_CC}"
    DEPENDS ${v8_extra_library_files}
    COMMAND python
    ARGS "${CMAKE_CURRENT_SOURCE_DIR}/tools/js2c.py" "${EXTRA_LIBRARIES_CC}" "EXTRAS"
         ${v8_extra_library_files}
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    VERBATIM
)

add_custom_target(v8_libraries_cc DEPENDS "${LIBRARIES_CC}")
add_custom_target(v8_experimental_libraries_cc DEPENDS "${EXPERIMENTAL_LIBRARIES_CC}")
add_custom_target(v8_extra_libraries_cc DEPENDS "${EXTRA_LIBRARIES_CC}")

add_library(v8 STATIC
    "${EXPERIMENTAL_LIBRARIES_CC}"
    "${EXTRA_LIBRARIES_CC}"
    "${LIBRARIES_CC}"
    src/accessors.cc
    src/allocation.cc
    src/allocation-site-scopes.cc
    src/allocation-tracker.cc
    src/api.cc
    src/api-natives.cc
    src/arguments.cc
    src/assembler.cc
    src/assert-scope.cc
    src/ast.cc
    src/ast-numbering.cc
    src/ast-value-factory.cc
    src/background-parsing-task.cc
    src/bailout-reason.cc
    src/base/atomicops_internals_x86_gcc.cc
    src/base/bits.cc
    src/base/cpu.cc
    src/base/division-by-constant.cc
    src/base/functional.cc
    src/base/logging.cc
    src/base/once.cc
    src/base/platform/condition-variable.cc
    src/base/platform/mutex.cc
    src/base/platform/platform-linux.cc
    src/base/platform/platform-posix.cc
    src/base/platform/semaphore.cc
    src/base/platform/time.cc
    src/base/sys-info.cc
    src/base/utils/random-number-generator.cc
    src/basic-block-profiler.cc
    src/bignum.cc
    src/bignum-dtoa.cc
    src/bit-vector.cc
    src/bootstrapper.cc
    src/builtins.cc
    src/cached-powers.cc
    src/char-predicates.cc
    src/checks.cc
    src/code-factory.cc
    src/codegen.cc
    src/code-stubs.cc
    src/code-stubs-hydrogen.cc
    src/compilation-cache.cc
    src/compilation-dependencies.cc
    src/compilation-statistics.cc
    src/compiler/access-builder.cc
    src/compiler/all-nodes.cc
    src/compiler/ast-graph-builder.cc
    src/compiler/ast-loop-assignment-analyzer.cc
    src/compiler/basic-block-instrumentor.cc
    src/compiler.cc
    src/compiler/change-lowering.cc
    src/compiler/code-generator.cc
    src/compiler/common-node-cache.cc
    src/compiler/common-operator.cc
    src/compiler/common-operator-reducer.cc
    src/compiler/control-builders.cc
    src/compiler/control-equivalence.cc
    src/compiler/control-flow-optimizer.cc
    src/compiler/control-reducer.cc
    src/compiler/frame-elider.cc
    src/compiler/frame-states.cc
    src/compiler/gap-resolver.cc
    src/compiler/graph.cc
    src/compiler/graph-reducer.cc
    src/compiler/graph-replay.cc
    src/compiler/graph-visualizer.cc
    src/compiler/instruction.cc
    src/compiler/instruction-selector.cc
    src/compiler/js-builtin-reducer.cc
    src/compiler/js-context-specialization.cc
    src/compiler/js-generic-lowering.cc
    src/compiler/js-graph.cc
    src/compiler/js-inlining.cc
    src/compiler/js-intrinsic-lowering.cc
    src/compiler/js-operator.cc
    src/compiler/js-typed-lowering.cc
    src/compiler/js-type-feedback.cc
    src/compiler/jump-threading.cc
    src/compiler/linkage.cc
    src/compiler/liveness-analyzer.cc
    src/compiler/load-elimination.cc
    src/compiler/loop-analysis.cc
    src/compiler/loop-peeling.cc
    src/compiler/machine-operator.cc
    src/compiler/machine-operator-reducer.cc
    src/compiler/machine-type.cc
    src/compiler/move-optimizer.cc
    src/compiler/node-cache.cc
    src/compiler/node.cc
    src/compiler/node-marker.cc
    src/compiler/node-matchers.cc
    src/compiler/node-properties.cc
    src/compiler/opcodes.cc
    src/compiler/operator.cc
    src/compiler/operator-properties.cc
    src/compiler/osr.cc
    src/compiler/pipeline.cc
    src/compiler/pipeline-statistics.cc
    src/compiler/raw-machine-assembler.cc
    src/compiler/register-allocator.cc
    src/compiler/register-allocator-verifier.cc
    src/compiler/register-configuration.cc
    src/compiler/schedule.cc
    src/compiler/scheduler.cc
    src/compiler/select-lowering.cc
    src/compiler/simplified-lowering.cc
    src/compiler/simplified-operator.cc
    src/compiler/simplified-operator-reducer.cc
    src/compiler/source-position.cc
    src/compiler/state-values-utils.cc
    src/compiler/tail-call-optimization.cc
    src/compiler/typer.cc
    src/compiler/value-numbering-reducer.cc
    src/compiler/verifier.cc
    src/compiler/x64/code-generator-x64.cc
    src/compiler/x64/instruction-selector-x64.cc
    src/compiler/x64/linkage-x64.cc
    src/compiler/zone-pool.cc
    src/contexts.cc
    src/conversions.cc
    src/counters.cc
    src/cpu-profiler.cc
    src/date.cc
    src/dateparser.cc
    src/debug.cc
    src/deoptimizer.cc
    src/disassembler.cc
    src/diy-fp.cc
    src/dtoa.cc
    src/elements.cc
    src/elements-kind.cc
    src/execution.cc
    src/extensions/externalize-string-extension.cc
    src/extensions/free-buffer-extension.cc
    src/extensions/gc-extension.cc
    src/extensions/statistics-extension.cc
    src/extensions/trigger-failure-extension.cc
    src/factory.cc
    src/fast-dtoa.cc
    src/fixed-dtoa.cc
    src/flags.cc
    src/frames.cc
    src/full-codegen.cc
    src/func-name-inferrer.cc
    src/gdb-jit.cc
    src/global-handles.cc
    src/handles.cc
    src/heap/gc-idle-time-handler.cc
    src/heap/gc-tracer.cc
    src/heap/heap.cc
    src/heap/identity-map.cc
    src/heap/incremental-marking.cc
    src/heap/mark-compact.cc
    src/heap/objects-visiting.cc
    src/heap-profiler.cc
    src/heap-snapshot-generator.cc
    src/heap/spaces.cc
    src/heap/store-buffer.cc
    src/hydrogen-bce.cc
    src/hydrogen-bch.cc
    src/hydrogen-canonicalize.cc
    src/hydrogen.cc
    src/hydrogen-check-elimination.cc
    src/hydrogen-dce.cc
    src/hydrogen-dehoist.cc
    src/hydrogen-environment-liveness.cc
    src/hydrogen-escape-analysis.cc
    src/hydrogen-gvn.cc
    src/hydrogen-infer-representation.cc
    src/hydrogen-infer-types.cc
    src/hydrogen-instructions.cc
    src/hydrogen-load-elimination.cc
    src/hydrogen-mark-deoptimize.cc
    src/hydrogen-mark-unreachable.cc
    src/hydrogen-osr.cc
    src/hydrogen-range-analysis.cc
    src/hydrogen-redundant-phi.cc
    src/hydrogen-removable-simulates.cc
    src/hydrogen-representation-changes.cc
    src/hydrogen-sce.cc
    src/hydrogen-store-elimination.cc
    src/hydrogen-types.cc
    src/hydrogen-uint32-analysis.cc
    src/i18n.cc
    src/ic/access-compiler.cc
    src/ic/call-optimization.cc
    src/ic/handler-compiler.cc
    src/ic/ic.cc
    src/ic/ic-compiler.cc
    src/ic/ic-state.cc
    src/ic/stub-cache.cc
    src/icu_util.cc
    src/ic/x64/access-compiler-x64.cc
    src/ic/x64/handler-compiler-x64.cc
    src/ic/x64/ic-compiler-x64.cc
    src/ic/x64/ic-x64.cc
    src/ic/x64/stub-cache-x64.cc
    src/interface-descriptors.cc
    src/interpreter-irregexp.cc
    src/isolate.cc
    src/jsregexp.cc
    src/layout-descriptor.cc
    src/libplatform/default-platform.cc
    src/libplatform/task-queue.cc
    src/libplatform/worker-thread.cc
    src/lithium-allocator.cc
    src/lithium.cc
    src/lithium-codegen.cc
    src/liveedit.cc
    src/log.cc
    src/log-utils.cc
    src/lookup.cc
    src/messages.cc
    src/modules.cc
    src/objects.cc
    src/objects-debug.cc
    src/objects-printer.cc
    src/optimizing-compile-dispatcher.cc
    src/ostreams.cc
    src/parser.cc
    src/pending-compilation-error-handler.cc
    src/perf-jit.cc
    src/preparse-data.cc
    src/preparser.cc
    src/prettyprinter.cc
    src/profile-generator.cc
    src/property.cc
    src/regexp-macro-assembler.cc
    src/regexp-macro-assembler-irregexp.cc
    src/regexp-macro-assembler-tracer.cc
    src/regexp-stack.cc
    src/rewriter.cc
    src/runtime-profiler.cc
    src/runtime/runtime-array.cc
    src/runtime/runtime.cc
    src/runtime/runtime-classes.cc
    src/runtime/runtime-collections.cc
    src/runtime/runtime-compiler.cc
    src/runtime/runtime-date.cc
    src/runtime/runtime-debug.cc
    src/runtime/runtime-function.cc
    src/runtime/runtime-generator.cc
    src/runtime/runtime-i18n.cc
    src/runtime/runtime-internal.cc
    src/runtime/runtime-json.cc
    src/runtime/runtime-literals.cc
    src/runtime/runtime-liveedit.cc
    src/runtime/runtime-maths.cc
    src/runtime/runtime-numbers.cc
    src/runtime/runtime-object.cc
    src/runtime/runtime-observe.cc
    src/runtime/runtime-proxy.cc
    src/runtime/runtime-regexp.cc
    src/runtime/runtime-scopes.cc
    src/runtime/runtime-strings.cc
    src/runtime/runtime-symbol.cc
    src/runtime/runtime-test.cc
    src/runtime/runtime-typedarray.cc
    src/runtime/runtime-uri.cc
    src/safepoint-table.cc
    src/sampler.cc
    src/scanner.cc
    src/scanner-character-streams.cc
    src/scopeinfo.cc
    src/scopes.cc
    src/snapshot/serialize.cc
    src/snapshot/snapshot-common.cc
    src/snapshot/snapshot-empty.cc
    src/snapshot/snapshot-source-sink.cc
    src/string-builder.cc
    src/string-search.cc
    src/strings-storage.cc
    src/string-stream.cc
    src/strtod.cc
    src/strtod.cc
    src/third_party/fdlibm/fdlibm.cc
    src/token.cc
    src/transitions.cc
    src/type-feedback-vector.cc
    src/type-info.cc
    src/types.cc
    src/typing.cc
    src/unicode.cc
    src/unicode-decoder.cc
    src/utils.cc
    src/v8.cc
    src/v8threads.cc
    src/variables.cc
    src/version.cc
    src/x64/assembler-x64.cc
    src/x64/builtins-x64.cc
    src/x64/codegen-x64.cc
    src/x64/code-stubs-x64.cc
    src/x64/cpu-x64.cc
    src/x64/debug-x64.cc
    src/x64/deoptimizer-x64.cc
    src/x64/disasm-x64.cc
    src/x64/frames-x64.cc
    src/x64/full-codegen-x64.cc
    src/x64/interface-descriptors-x64.cc
    src/x64/lithium-codegen-x64.cc
    src/x64/lithium-gap-resolver-x64.cc
    src/x64/lithium-x64.cc
    src/x64/macro-assembler-x64.cc
    src/x64/regexp-macro-assembler-x64.cc
    src/zone.cc
)

add_dependencies(v8 v8_libraries_cc)
add_dependencies(v8 v8_experimental_libraries_cc)
add_dependencies(v8 v8_extra_libraries_cc)
