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
        $files = $this->wrapper->implementsInterface('foo')->toImmVector();
        expect($files->count())->toBe(0);
      });
    });
  });
  describe('subclassOf()', function () {
    context('when unmatched', function () {
      it('class file does not return', function () {
        $files = $this->wrapper->subclassOf('foo')->toImmVector();
        expect($files->count())->toBe(0);
      });
    });
  });
  describe('startsWith()', function () {
    context('when matched', function () {
      it('returns matched class files', function () {
        $files = $this->wrapper->startsWith('Ex')->toImmVector();
        expect($files->count())->toBe(1);
      });
    });
  });
  describe('endsWith()', function () {
    context('when matched', function () {
      it('returns matched class files', function () {
        $files = $this->wrapper->endsWith('1')->toImmVector();
        expect($files->count())->toBe(1);
      });
    });
  });
});
