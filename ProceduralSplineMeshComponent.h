// Copyright © eezstreet 2024, All Rights Reserved
// The following is a snippet of the ProceduralSplineMeshComponent.h that is included with the "SuperSplineMesh" plugin.
// It is intended for documentation purposes only. Your code will not work if you attempt to use this header!

// Uncomment to enable profiling functions
//#define _PROFILING_PROCEDURALSPLINEMESH

UCLASS(Blueprintable)
class UProceduralSplineMeshComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	/** The mesh to use by default. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SuperSplineMesh|Procedural Spline Mesh Component")
	UStaticMesh* DefaultStaticMesh;

	/** The length of each mesh in the spline. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SuperSplineMesh|Procedural Spline Mesh Component")
	float DefaultMeshLength;

	/** Which segments of the static mesh to use. */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "SuperSplineMesh|Procedural Spline Mesh Component")
	TArray<int32> MeshSectionsToUse;

	/**
	 *	Whether to generate collision for the procedural mesh.
	 *	**NOTE:** Only takes effect on mesh refresh.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SuperSplineMesh|Procedural Spline Mesh Component")
	bool bCreateCollision;

	/** Whether refreshing the mesh also automatically refreshes the navigation. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SuperSplineMesh|Procedural Spline Mesh Component")
	bool bAutoUpdateNavigation = true;

	/** How far along the spline to start the mesh. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SuperSplineMesh|Procedural Spline Mesh Component")
	float StartOffset = 0.0f;

	/** How far from the end of the spline to end the mesh. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SuperSplineMesh|Procedural Spline Mesh Component")
	float EndOffset = 0.0f;

	/** How much should we scale the mesh by? */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SuperSplineMesh|Procedural Spline Mesh Component")
	FVector2D MeshScale = FVector2D(1.0f);

	/** How much spacing should we put in between each sub-mesh? */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SuperSplineMesh|Procedural Spline Mesh Component")
	FVector2D InterMeshDistance = FVector2D(0.0f);

	/** Should we use Hermite roll interpolation? */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SuperSplineMesh|Procedural Spline Mesh Component")
	bool bUseInterpHermite = false;

	/** 
	 *	Whether the material of the mesh should be overridden. If turned off, the original material of the mesh will be preserved. 
	 *	**NOTE:** Changes to this do not trigger a mesh refresh.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SuperSplineMesh|Procedural Spline Mesh Component|Material")
	bool bOverrideMaterial;

	/** 
	 *	What material to overwrite the mesh with.
	 *	**NOTE:** Changes to this do not trigger a mesh refresh.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SuperSplineMesh|Procedural Spline Mesh Component|Material")
	UMaterialInterface* OverrideMaterial;

	/**
	 *	What axis to use.
	 *	**NOTE:** Changes to this do not trigger a mesh refresh.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SuperSplineMesh|Procedural Spline Mesh Component")
	TEnumAsByte<ESplineMeshAxis::Type> SplineAxis;

	/**
	 *	Has no effect unless plugin compiled with _PROFILING_PROCEDURALSPLINEMESH.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SuperSplineMesh|Procedural Spline Mesh Component|Debug")
	bool bProfilePerformance;

	/**
	 *	What Procedural Mesh Component we should be targetting.
	 *	This should be set on the Construction script of your blueprint.
	 */
	UPROPERTY(BlueprintReadWrite, Category = "SuperSplineMesh|Procedural Spline Mesh Component")
	class UProceduralMeshComponent* TargetMeshComponent;

	/**
	 *	What Spline Component we should be targetting.
	 *	This should be set on the Construction script of your blueprint.
	 */
	UPROPERTY(BlueprintReadWrite, Category = "SuperSplineMesh|Procedural Spline Mesh Component")
	USplineComponent* TargetSplineComponent;

	/** The data for all of the points in the spline mesh. */
	UPROPERTY(BlueprintReadOnly, Category = "SuperSplineMesh|Procedural Spline Mesh Component")
	TArray<FProceduralSplineMeshPoint> PointData;

	/**
	 *	Refreshes the navigation for the mesh.
	 */
	UFUNCTION(BlueprintCallable, Category = "SuperSplineMesh|Procedural Spline Mesh Component")
	void RefreshNavigation();

	/**
	 *	How long should this section of the mesh be?
	 *	By default, this is the same as `DefaultMeshLength`.
	 *	@param SplinePointIndex the spline point index we are querying
	 *	**NOTE:** A change in this return value will cause a mesh refresh.
	 */
	UFUNCTION(BlueprintNativeEvent, Category = "SuperSplineMesh|Procedural Spline Mesh Component")
	float GetMeshLengthForProceduralSplineMesh(int32 SplinePointIndex);

	/**
	 *	What static mesh should be rendered at this position?
	 *	@param SplinePointIndex the spline point index we are querying
	 *	@param SubMeshIndex the segment within the spline point that we are querying
	 *	**NOTE:** A change in mesh here does not cause a mesh refresh.
	 *  **NOTE:** Materials are shared amongst all meshes within a segment.
	 */
	UFUNCTION(BlueprintNativeEvent, Category = "SuperSplineMesh|Procedural Spline Mesh Component")
	UStaticMesh* GetStaticMeshForProceduralSplineMesh(int32 SplinePointIndex, int32 SubMeshIndex);

	/**
	 *	What material should be used at this spline point?
	 *	@param SplinePointIndex the spline point index we are querying
	 *	@param MeshSection the section of the mesh that we are rendering (NOT the SubMeshIndex!!)
	 *	**NOTE:** A change in material here does not cause a mesh refresh.
	 */
	UFUNCTION(BlueprintNativeEvent, Category = "SuperSplineMesh|Procedural Spline Mesh Component")
	UMaterialInterface* GetMaterialForProceduralSplineMesh(int32 SplinePointIndex, int32 MeshSection);

	/**
	 *	What LOD should be used for this submesh?
	 *	@param SplinePointIndex the spline point that we are querying
	 *	@param SubMeshIndex the segment within the spline point that we are querying
	 *	**NOTE:** A change in LOD here does not cause a mesh refresh.
	 */
	UFUNCTION(BlueprintNativeEvent, Category = "SuperSplineMesh|Procedural Spline Mesh Component")
	int32 GetLodForProceduralSplineMesh(int32 SplinePointIndex, int32 SubMeshIndex);

	/**
	 *	An implementable event that fires off when points in the spline mesh get modified.
	 *	This may fire off multiple times per tick:
	 *   * On automatic mesh regenerations
	 *   * On mesh regenerated from queued regenerations
	 *   * On point added to spline mesh
	 *   * On point removed from spline mesh
	 *	@param PointsModified - the indices of the points that were modified
	 */
	UFUNCTION(BlueprintImplementableEvent, Category = "SuperSplineMesh|Procedural Spline Mesh Component")
	void OnMeshRegenerated(const TArray<int32>& PointsModified);

	/**
	 *	Internal function. Used to get the render index.
	 *	@param SplinePointIndex the spline point that we are querying
	 *	@param MeshSectionIndex the section of the mesh that we are rendering (NOT the SubMeshIndex!!)
	 */
	UFUNCTION(BlueprintPure, Category = "SuperSplineMesh|Procedural Spline Mesh Component")
	int32 GetRenderIndex(int32 SplinePointIndex, int32 MeshSectionIndex) const;

	/**
	 *	Internal function. Used to get the length of a specific spline mesh. NOT to be confused with the sub mesh length.
	 *	@param SplinePointIndex the spline point that we are querying
	 */
	UFUNCTION(BlueprintPure, Category = "SuperSplineMesh|Procedural Spline Mesh Component")
	float GetSegmentLength(int32 SplinePointIndex) const;


	 /**
	  *	Optimized add for spline points.
	  *	You want to call this function instead of updating the spline component for more optimized mesh generation.
	  * @param Position where to add the new spline point
	  * @param CoordinateSpace what coordinate space we are working with
	  */
	UFUNCTION(BlueprintCallable, Category = "SuperSplineMesh|Procedural Spline Mesh Component")
	void AddSplinePoint(const FVector& Position, ESplineCoordinateSpace::Type CoordinateSpace);

	/**
	 *	Optimized insert for spline points.
	 *	You want to call this function instead of updating the spline component for more optimized mesh generation.
	 *	@param Position where to add the new spline point
	 *	@param Index which index in the spline to insert the spline point into
	 *	@param CoordinateSpace what coordinate space we are working with
	 */
	UFUNCTION(BlueprintCallable, Category = "SuperSplineMesh|Procedural Spline Mesh Component")
	void AddSplinePointAtIndex(const FVector& Position, int32 Index, ESplineCoordinateSpace::Type CoordinateSpace);

	/**
	 *	Optimized remove for spline points.
	 *	You want to call this function instead of updating the spline component for more optimized mesh generation.
	 */
	UFUNCTION(BlueprintCallable, Category = "SuperSplineMesh|Procedural Spline Mesh Component")
	void RemoveLastSplinePoint();

	/**
	 *	Optimized RemoveAt function for spline points.
	 *	You want to call this function instead of updating the spline component for more optimized mesh generation.
	 *	@param Index which spline point to remove
	 */
	UFUNCTION(BlueprintCallable, Category = "SuperSplineMesh|Procedural Spline Mesh Component")
	void RemoveSplinePointAt(int32 Index);

	/**
	 *	Force a refresh at the specified spline points.
	 *	@param SplinePoints the spline points to update
	 */
	UFUNCTION(BlueprintCallable, Category = "SuperSplineMesh|Procedural Spline Mesh Component")
	void RefreshAtSplinePoints(const TArray<int32>& Points);

	/**
	 *	Force the entire mesh to be rebuilt.
	 */
	UFUNCTION(BlueprintCallable, Category = "SuperSplineMesh|Procedural Spline Mesh Component")
	void RebuildEntireMesh();

	/**
	 *	Clear all mesh sections for a particular point.
	 *	@param PointIndex the point that we are clearing meshes for
	 */
	UFUNCTION(BlueprintCallable, Category = "SuperSplineMesh|Procedural Spline Mesh Component")
	void ClearAllMeshesForPoint(int32 PointIndex);

	/**
	 *	Turn on/off collision on the entire mesh.
	 *	@param bNewCollision true if collision should be enabled, false otherwise
	 *	@param bMultiThreaded true if this function should be multithreaded, false otherwise
	 */
	UFUNCTION(BlueprintCallable, Category = "SuperSplineMesh|Procedural Spline Mesh Component")
	void SetSplineMeshCollision(bool bNewCollision);

	/**
	 *	Turn on/off collision on a specific point.
	 *	@param bNewCollision true if collision should be enabled, false otherwise
	 *	@param PointIndex which point to turn on/off collision at
	 */
	UFUNCTION(BlueprintCallable, Category = "SuperSplineMesh|Procedural Spline Mesh Component")
	void SetSplineMeshCollisionAtPoint(bool bNewCollision, int32 PointIndex);

	/**
	 *	Turn on/off visibility at a specific point.
	 *	@param bNewVisibility true if the point should be visible, false otherwise
	 *	@param PointIndex which point to turn on/off visibility at
	 */
	UFUNCTION(BlueprintCallable, Category = "SuperSplineMesh|Procedural Spline Mesh Component")
	void SetSplineMeshVisibilityAtPoint(bool bNewVisibility, int32 PointIndex);
};