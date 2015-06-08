class ResourceCapsule(object):
    def __init__(self, resource_manager, key):
        self._res = resource_manager
        self._key = key

    def __call__(self):
        return self._res[self._key]