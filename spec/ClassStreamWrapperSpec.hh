<?hh //partial

namespace package\spec;

use package\ClassFile;
use package\ClassStreamWrapper;

describe(ClassStreamWrapper::class, function () {
  beforeEach(function () {
    $stream = () ==> {
      yield new ClassFile(
        realpath(__DIR__ . '/fixtures/Example1.hh'),
        'package\\spec\\fixtures',
        realpath(__DIR__ . '/fixtures')
      );
    };
    $this->wrapper = new ClassStreamWrapper($stream());
  });
  describe('implementsInterface()', function () {
    context('when unmatched', function () {
      it('class file does not return', function () {
        $items = Vector {};
        $files = $this->wrapper->implementsInterface('foo');

        foreach ($files as $file) {
          $items->add($file);
        }
        expect($items->count())->toBe(0);
      });
    });
  });
  describe('subclassOf()', function () {
    context('when unmatched', function () {
      it('class file does not return', function () {
        $items = Vector {};
        $files = $this->wrapper->subclassOf('foo');

        foreach ($files as $file) {
          $items->add($file);
        }
        expect($items->count())->toBe(0);
      });
    });
  });
});
